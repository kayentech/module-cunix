#include "test.h"
#include<stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include<string.h>
#include<stdarg.h>
#include <sys/syscall.h>


int my_atoi(const char *nptr){
  int n = strlen(nptr);
  int res = 0;
  int mult = 1;
  char c;
  int i = n-1;

  while ((i>=0) && (('0'>nptr[i])||(nptr[i]>'9')))
    i--;
  for(; i>=0 ; i--){
    c = nptr[i];
    if((c == '-') || !(('0' <= c)&&( c <= '9')))
      break;
    res = res + mult*(c - '0' );
    mult = mult*10;
  }
  return c == '-'?-res:res;
};

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
char my_putcharr(const char* str){
  return write(1 , str, sizeof(char));
};

int my_puts(const char *s){
  return write(1, s, (strlen(s)*sizeof(char)));
};

unsigned int my_strlen(char *str){
  int i = 0;
  while (str[i] != '\0')
    i++;
  return i;
};

typedef struct status{
   int minus;
   int zero;
   int padding;
   int d;
   int s;
} format_status;

void print_format_arg(format_status* fs, va_list** args){
  char* par;
  char* par_res;
  int val_list_neg = 0;
  if(fs->s)
    par = va_arg(**args, char*);
  else if(fs->d){
    par = my_itoa(va_arg(**args, int));
    if (par[0] == '-'){
      val_list_neg = 1;
    }
  }

if(fs->padding){
    char fill_c;
    if(fs->zero)
      fill_c = '0';
    else
      fill_c = ' ';
      int shift = fs->padding - my_strlen(par);
    if(shift > 0){
      par_res = (char*) calloc((my_strlen(par)+shift+1),sizeof(char));
      if(fs->minus){
        char* filling = (char*)calloc(shift+1, sizeof(char));
        memset(filling, fill_c, shift);
        filling[shift] = '\0';
        strcpy(par_res, par);
        strcat(par_res, filling);
      }
      else{
        memset(par_res, fill_c, shift);
        par_res[shift] = '\0';
        strcat(par_res, par); 

        if(val_list_neg && (fill_c == '0')){
          par_res[0] = '-';
          par_res[my_strlen(par_res) - my_strlen(par)] = '0';
        }
      }
    }
    else
      par_res = par;
  }
  else
    par_res = par;
    my_puts(par_res);
}

int parse_integer(const char** str){
  const char* c = *str;
  int i = 0;
  while(c[i] && ('0'<= c[i] ) && (c[i]<='9')){
    i++;
  }
  char substr[i+1];
  memcpy(substr, *str, i);
  substr[i] = '\0';
  *str=*str+i;
  return atoi(substr);
}


int percent(const char**c, va_list** args){
  format_status status = {0};
  char cur = **c; 
  if(**c == '%'){
    my_putcharr(*c);
    (*c)++;
    return 1;
  }

  if(**c == '-'){ 
    status.minus = 1;
    (*c)++;
    if(!**c)
     return 0; 
  }
  if(**c == '0'){
    status.zero = 1;
    (*c)++;
    if(!**c)
      return 0;
  }

  if(('0'<=**c) && (**c <= '9'))
    status.padding = parse_integer(c);
  if(!**c)
    return 0;

  if(**c == 'd'){
    status.d = 1;
    (*c)++;
  }
  else if(**c == 's'){
    status.s = 1;
    (*c)++;
  }
  print_format_arg(&status, args);
  return 1;
}

int check(const char** c, va_list** args){
  if(!**c)
    return 0;
  if(**c == '%'){
    (*c)++;
    return percent(c, args);
  }
  my_putcharr(*c);
  (*c)++;
  return 1;
}
int my_printf(const char *format, ...){
   va_list args;
   va_start(args, format);
   va_list* args_ptr = &args;
   va_list** args_dptr = &args_ptr;

   const char** c = &format; 
   while (check(c, args_dptr)){};
}