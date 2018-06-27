#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "utils.h"
#include "vm_filler.h"

int       parse_command_line(vmcore_t *vm, int argc, char** argv)
{
  char    *playinfo;
  int     option = 0;
  int     nbplayers;

  nbplayers = 0;
  if (argc == 1)
    fail("Usage: vm_filler -p <path_to_compiled_filler> -m <path_to_start_map>\n", EXIT_FAILURE);
  while ((option = getopt(argc, argv, "m:p:")) != -1)     //parse the comand line
  {
    switch (option) {
      case 'm':
        vm->mapfile = optarg;
        break;

      case 'p':
        {
          playinfo = optarg;
          vm->players[nbplayers]->filepath = playinfo;
          nbplayers++;
        }
    }
  }
  return nbplayers;
}

void      read_map(vmcore_t *vm)
{
  FILE    *fp;
  int     n,m;
  char    ch;
  char    **curr;

  fp = fopen(vm->mapfile, "r");
  if (fp == NULL)
    fail("Start map file doesn't exist\n", EXIT_FAILURE);
  fscanf(fp, "%d %d", &n, &m);
  fscanf(fp, "%c", &ch);
  vm->map.w = m;
  vm->map.h = n;
  curr = malloc(n * sizeof(char*));
  for (int i = 0; i < n; i++)
    curr[i] = malloc(m * sizeof(char));

  vm->map.array = curr;
  char c;
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < m; j++)
    {
      fscanf(fp, "%c",&vm->map.array[i][j]);
    }
    fscanf(fp,"%c",&c);
  }
  fclose(fp);
}

void      create_log(vmcore_t *vm)
{
  int     fd;

  fd = open("vm_filler.log", O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
  if (fd < 0)
    fail("open(vm_filler.log) failed and return = %d\n", fd);
  vm->log_fd = fd;

  dprintf(vm->log_fd, "initializing vm core\n");
}

int       init_core(vmcore_t *vm, int argc, char** argv)
{
  int     nbplayers = 0;

  srand(time(NULL));
  create_log(vm);
  vm->turn = 0;
  vm->current_elem = NULL;
  vm->status = PLAYER_REQUEST;

  for (int i = 0; i < MAX_PLAYERS; i++)
  {
    vm->players[i] = malloc(sizeof(player_t));
  }
  nbplayers = parse_command_line(vm, argc, argv);
  vm->nbplayers = nbplayers;
  dprintf(vm->log_fd, "number of players: %d\n", vm->nbplayers);
  for (int i = 0; i < vm->nbplayers; i++)                   //write players info
  {
    vm->players[i]->symbol = get_symbol(i);
    vm->players[i]->color =get_color(i);
    vm->players[i]->in_game = 0;
    dprintf(vm->log_fd,"player:%d  file:%s  symbol:%c  color:%d\n", i, vm->players[i]->filepath, vm->players[i]->symbol, vm->players[i]->color);
  }
  dprintf(vm->log_fd, "map file:%s\n", vm->mapfile);
  read_map(vm);
  dprintf(vm->log_fd,"----------\n");
  return 0;
}

void      destroy_core(vmcore_t *vm)
{
  for (int i = 0; i < vm->map.h; i++)
    free(vm->map.array[i]);
  free(vm->map.array);
  for(int i = 0; i < vm->current_elem->h; i++)
    free(vm->current_elem->array[i]);
  free(vm->current_elem->array);
  free(vm->current_elem);
  for (int i = 0; i < MAX_PLAYERS; i++)
    free(vm->players[i]);
}
