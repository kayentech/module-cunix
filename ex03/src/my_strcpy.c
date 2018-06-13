#include "test.h"

char *my_strcpy(char *dest, const char *src){
  char *s1 = dest;
  while ((*s1++ = *src++) != 0);
return (dest);
};  
