#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <stdio.h>

char* my_itoa(int nmb) {
  char *ptr, *buf;
  buf = malloc(16 * sizeof(char));
  ptr = buf;
  int i = 1, n;

  if (nmb < 0) {
    nmb = -1 * nmb;
    *buf = '-';
    buf++;
  }

  n = nmb;

  while (n > 9) {
    n /= 10;
    i *= 10;
  }

  while (i > 0) {
    n = nmb / i;
    *buf = '0' + n;
    buf++;
    nmb -= i * n;
    i /= 10;
  }
  *buf = '\0';

  return ptr;
}

int my_printf(const char* format, ...) {
  extern long write(int, const char*, unsigned int);

  va_list arg_list;
  unsigned char symb;
  char *st, *padd_str, *str, *padd_str_init, *str_start_ptr;
  int padding;

  str = malloc(256 * sizeof(char));
  str_start_ptr = str;
  padd_str_init = malloc(16 * sizeof(char));
  va_start(arg_list, format);

  while(*format != '\0') {

    if(*format == '%') {
      padding = 0;
      symb = 0;
      padd_str = padd_str_init;

      format++;
      while(*format != ' ' && *format != '\0') {
        if(*format == '%'){
          *str = '%';
          str++;
          format++;
          break;
        }
        if(*format == '0'){
          symb = '0';
          format++;
        }
        while(*format >= '0' && *format <= '9') {
          *padd_str = *format;
          padd_str++;
          format++;
        }
        *padd_str = '\0';
        padding = atoi(padd_str_init);
        if(*format == 's'){
          st = va_arg(arg_list, char *);
        }
        if(*format == 'd'){
          int i = va_arg(arg_list, int);
          st = my_itoa(i);
        }
        padding -= strlen(st);
        while(padding-- > 0) *str++ = (symb)?symb:' ';
        while(*st != '\0') {
          *str = *st;
          str++;
          st++;
        }
        format++;
        break;
      }
      continue;
    }
    *str = *format;
    str++;
    format++;
  }
  *str = '\0';

  write(1, str_start_ptr, strlen(str_start_ptr));
  va_end(arg_list);
  free(padd_str_init);
  free(str_start_ptr);
  return 0;
}

/*int main() {
    my_printf("%s\n", "Hello Printf");
  my_printf("We need 100%% of %s\n", "use case");
  my_printf("It's %s's %s (%s)\n", "iGor", "phone", "TEXT");
  my_printf("[%10s] [%4s] [%8s] [%12s]\n", "THIS", "IS", "PADDED", "TEXT");
  my_printf("%d\n", 42);
  my_printf("%d %s\n", 42, "is the answer");
  my_printf("%010d %s\n", 42, "was padded on 10");
  my_printf("%10d %s\n", 42, "was also padded using spaces");

  return 0;
 }*/