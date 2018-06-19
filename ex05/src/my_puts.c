#include <stdio.h>
int my_puts(const char *s){
  int answ = printf("%s\n", s);
  return (answ > 0) ? answ : EOF;
}
