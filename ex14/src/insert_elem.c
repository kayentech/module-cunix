#include "vm_filler.h"
#include <stdio.h>
#include <stdlib.h>

int check_free_space(map_t *map, elem_t *new_elem, pos_t p)
{
  for(int i = 0; i < new_elem->h; i++)
    for(int j = 0; j < new_elem->w; j++)
      if(new_elem->array[i][j] == '*')
      {
        if(i+p.y < map->h && j+p.x < map->w && i+p.y >= 0 && j+p.x >= 0)
        {
          if(map->array[i+p.y][j+p.x] != '.')
            return -1;
        }
        else
         return -1;
      }
  return 0;
}

int check_connection(map_t *map, elem_t *new_elem, pos_t p, char symbol)
{
  for(int i = 0; i < new_elem->h; i++)
    for(int j = 0; j < new_elem->w; j++)
      if(new_elem->array[i][j] != '.')
      {
        if(i+p.y+1 < map->h && map->array[i+p.y+1][j+p.x] == symbol)
            return 0;
        if (i+p.y-1 >= 0 && map->array[i+p.y-1][j+p.x] == symbol)
            return 0;
        if (j+p.x+1 < map->w && map->array[i+p.y][j+p.x+1] == symbol)
            return 0;
        if (j+p.x-1 >= 0 && map->array[i+p.y][j+p.x-1] == symbol)
            return 0;
      }
  return -1;
}

int check_rules(map_t *map, elem_t *new_elem, pos_t p, player_t *player)
{
  if (check_free_space(map, new_elem, p) == 0 &&
      check_connection(map, new_elem, p, player->symbol) == 0)
      return 0;
  return -1;
}


int insert_elem(map_t *map, elem_t *new_elem, pos_t p, player_t *player)
{
  if (check_rules(map, new_elem, p, player) != 0)
    return -1;
  else{
    for (int i = 0; i < new_elem->h; i++)
      for(int j = 0; j < new_elem->w; j++)
        if(new_elem->array[i][j] == '*')
          map->array[i+p.y][j+p.x] = player->symbol;
  }
  return 0;
}
