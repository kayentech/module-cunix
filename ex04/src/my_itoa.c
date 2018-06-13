#include "test.h"
#include<stdio.h>
#include <stdlib.h>

char* my_itoa(int nmb)
{
    char *str =(char*) malloc(100);
    char *answ = str;
    int num = nmb;
    int j = 1;
    
    if (num < 0 ){
      *str='-';
       str++;
       num=-num;
    };

    while (num > 9) {
      num = num/10;
      j=j*10;
    };

    while (j > 0) {
      num = nmb / j;
      *str = '0' + num;
      str++;
      nmb -= j * num;
      j =j/10;
  }
  *str = '\0';
  return answ;
};









