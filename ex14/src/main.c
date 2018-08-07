#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>

#include "vm_filler.h"

int          main(int argc, char **argv)
{
  vmcore_t   vm;

  srand(time(NULL));

  init_core(&vm, argc, argv);
  start_game(&vm);
  destroy_core(&vm);
  return 0;
}

