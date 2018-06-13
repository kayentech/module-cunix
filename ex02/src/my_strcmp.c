#include "test.h"

int my_strcmp(char *s1, char *s2){
  unsigned char *str1 = (unsigned char *)s1;
  unsigned char *str2 = (unsigned char *)s2; 
  unsigned int c1,c2;
  int i=0;
  while (str1[i]==str2[i]){
    c1+=str1[i];
    c2+=str2[i];
    i++;
    if(str1[i] == '\0'){
      return c1 - c2;
    };
  };
  return c1 - c2;
}

