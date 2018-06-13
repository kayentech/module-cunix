#include "test.h"
#include <unistd.h>

char my_putcharr(const char str){
  return write(1 , &str, 1);
};

int my_puts(const char *s){
  while(*s != '\0'){
    my_putcharr(*s++);
  };
  my_putcharr('\n');
  return 0;
};





