#ifndef VM_FILLER_H_
# define VM_FILLER_H_

# define MAX_PLAYERS (4)
# define MAX_ELEM_HEIGTH (7)
# define MAX_ELEM_WIDTH (7)

# define PLAYER_REQUEST (1)
# define PLAYER_ANSWER (2)

typedef struct  pos_s
{
  int        x;
  int        y;
}               pos_t;

typedef struct  elem_s
{
  int        w;
  int        h;
  char       **array;
}            elem_t;

typedef struct  map_s
{
  int        w;
  int        h;
  char       **array;
}               map_t;

typedef struct  player_s
{
  int           color;
  char          symbol;
  char          *filepath;
  int           in_game;          // 0 - in game; 1 - no
  int           in;
  int           out;
  int           player_id;
}               player_t;

typedef struct  vmcore_s
{
  int           logfd;
  char          *mapfile;
  map_t         map;
  player_t      *players[MAX_PLAYERS];
  int           nbplayers;
  int           turn;
  int           status;
  int           log_fd;
  elem_t        *current_elem;
}               vmcore_t;

/** elem functions **/
elem_t* create_elem();
int insert_elem(map_t *map, elem_t *new_elem, pos_t p, player_t *player);
int check_rules(map_t *map, elem_t *new_elem, pos_t p, player_t *player);
int   find_winner(vmcore_t *vm);

/** map functions **/
void print_map(vmcore_t *vm);
//void print_map_player(int fd, vmcore_t *vm, player_t *player);
void print(int fd, vmcore_t *vm);
/** core functions **/
int init_core(vmcore_t *vm, int argc, char** argv);
void destroy_core(vmcore_t *vm);

/** main functions **/
pos_t   parse_answer(char *answer);
void    exec_players_pool(vmcore_t *vm);
void    kill_players_pool(vmcore_t *vm);
void    start_game(vmcore_t *vm);
#endif  /* VM_FILLER_H_ */

