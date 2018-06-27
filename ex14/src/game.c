#include "vm_filler.h"
#include "insert.h"
#include "utils.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int         find_winner(vmcore_t *vm)
{
  int       max_index = 0;
  int       *res = malloc(vm->nbplayers*sizeof(int));

  for(int k = 0; k < vm->nbplayers; k++)
  {
    res[k] = 0;
    for(int i = 0; i < vm->map.h; i++)
      for(int j = 0; j < vm->map.w; j++)
        if(vm->map.array[i][j] == vm->players[k]->symbol)
          res[k]++;

    if (res[k] > res[max_index])
      max_index = k;
    else if (k != 0 && res[k] == res[max_index])
    { free(res);
      return -1;
  }
  }
  free(res);
  return max_index;
}

int         game_is_on(vmcore_t *vm)
{
  for (int i = 0; i < vm->nbplayers; i++)
    if(vm->players[i]->in_game == 0) return 0;
  return -1;
}

int         next_turn(vmcore_t *vm)
{
  return (vm->turn + 1) % vm->nbplayers;
}

void        write_turn(vmcore_t *vm, player_t *current_player)
{
  if(vm->current_elem != NULL)
  {
    for (int i=0; i<vm->current_elem->h; i++)
      free(vm->current_elem->array[i]);
    free(vm->current_elem->array);
    vm->current_elem->array = NULL;
    free(vm->current_elem);
    vm->current_elem = NULL;
  }
  vm->current_elem = create_elem();
  print (current_player->out, vm);
  print(vm->log_fd, vm);
  dprintf(vm->log_fd, "\n------------\n");
}

pos_t       parse_answer(char *answer)
{
  int       size;
  char      *part1, *part2;
  pos_t     p;

  size = strlen(answer);

  part1 = malloc(size);

  int i = 0;
  while(answer[i] != ' ')
  {
    part1[i] = answer[i];
    i++;
  }
  part1[i] = '\0';
  i++;

  part2 = malloc(size);
  int j = 0;
  while(answer[i] != '\0')
  {
    part2[j] = answer[i];
    i++;
    j++;
  }
  part2[j] = '\0';

  p.x = atoi(part1);
  p.y = atoi(part2);

  free(part1);
  free(part2);

  return p;
}

pos_t       reading_position(vmcore_t *vm, player_t *p)
{
  pos_t     pos;
  char      buffer[32] = {0};

  read(p->in, buffer, 32);
  dprintf(vm->log_fd, "Buffer: %s\n", buffer);
  if((buffer[0] > '9' || buffer[0] < '0') && buffer[0] != '-')
  {
    pos.x = -20;
    pos.y = -20;
    return pos;
  }
  pos = parse_answer(buffer);
  dprintf(vm->log_fd, "x=%d y=%d\n------------\n", pos.x, pos.y);
  return pos;
}

void  timeout_reset(struct timeval *timer)
{
  timer->tv_sec = 1;
  timer->tv_usec = 0;
}

void        polling_players(vmcore_t *vm)
{
  int       ret;
  pos_t     pos;
  fd_set    rfds;
  fd_set    wfds;
  int       max = 0;
  player_t  *current_player;
  struct timeval timeout;

  dprintf(vm->log_fd, "polling players\n");
  while(game_is_on(vm) == 0)
  {
    current_player = vm->players[vm->turn];
    while(current_player->in_game == 1)
    {
      vm->turn = next_turn(vm);
      current_player = vm->players[vm->turn];
    }

    FD_ZERO(&rfds);
    FD_ZERO(&wfds);
    switch (vm->status)
    {
      case PLAYER_REQUEST:
        FD_SET(current_player->out, &wfds);
        max = current_player->out;
        break;

      case PLAYER_ANSWER:
        FD_SET(current_player->in, &rfds);
        max = current_player->in;
        break;
    }

    timeout_reset(&timeout);
    ret = select(max + 1, &rfds, &wfds, NULL, &timeout);
    if (ret < 0) {
    }
    if (FD_ISSET(current_player->out, &wfds))
    {
      write_turn(vm, current_player);
      vm->status = PLAYER_ANSWER;
    }

    if (FD_ISSET(current_player->in, &rfds))
    {
      pos = reading_position(vm, current_player);
      if(insert_elem(&(vm->map),vm->current_elem, pos, vm->players[vm->turn]) != 0)
        vm->players[vm->turn]->in_game = 1;
      system("clear");
      print_map(vm);
      usleep(10000);
      vm->status = PLAYER_REQUEST;
      vm->turn = next_turn(vm);
    }
    if(ret == 0)
    {
      dprintf(vm->log_fd, "Player with symbol %c was stopped. Reason: no answer\n", vm->players[vm->turn]->symbol);
      vm->players[vm->turn]->in_game = 1;
      vm->turn = next_turn(vm);
      vm->status = PLAYER_REQUEST;
    }
  }
}

void      generate_start_points(vmcore_t *vm)
{
  dprintf(vm->log_fd, "generating start points\n");
  int     x,y;
  for (int i = 0; i < vm->nbplayers; i++)
  {
    x = rand()%vm->map.h;
    y = rand()%vm->map.w;
    vm->map.array[x][y] = vm->players[i]->symbol;
    dprintf(vm->log_fd, "%c x=%d y=%d\n", vm->players[i]->symbol, x, y);
  }
  dprintf(vm->log_fd, "-----------\n");
}

void        start_game(vmcore_t *vm)
{
  int       winner;

  dprintf(vm->log_fd, "starting the game\n-----------\n");
  generate_start_points(vm);
  exec_players_pool(vm);
  polling_players(vm);

  winner = find_winner(vm);
  if(winner == -1)
    printf("No winner\n");
  else
    printf("\n-------------\nthe winner is %s with symbol [%c]\n-------------\n",vm->players[winner]->filepath, vm->players[winner]->symbol);
  kill_players_pool(vm);
}
