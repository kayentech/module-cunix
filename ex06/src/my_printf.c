#include <math.h>
#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

// integer to string converting
char* my_itoa(int nmb) {
  if(nmb == 0) {
    char* none = malloc(sizeof(char));
    *none = '0';
    return none;
  }
  bool sign = false;
  if(nmb < 0) {
    sign = true;
    nmb*=-1;
  }
  int i = log10((double) abs(nmb)); // take number of charecters
  char* dest = malloc(i);
  while(nmb > 0){
    dest[i] = (nmb % 10) + '0';
    nmb/=10;
    i-=1;
  }
  if(sign) {
    for( int j = strlen(dest) - 1; j>=0 ; j--)
      dest[j+1] = dest[j];
      dest[0] = '-';
    }	
  dest[i] = '\0';
  return dest;
}

// string to integer converting
int my_atoi(const char *format)
{
  int sign = (*format == '-' ? -1 : 1);
  int indent = (sign == -1 ? 1 : 0);
  int num = 0;
  for ( ; *(format+indent) >= '0' && *(format+indent) <= '9'; indent++ )
    num = num*10 + (*(format+indent)-'0');
  return num*sign;
};

// get length of the string
unsigned int my_strlen(const char *str) 
{
  unsigned int len = 0;
  for( ; *(str+len) != '\0'; len++);
  return len;
};

// counting characters of string
int counter(const char *str)
{
 int i = 0;
 for( ; *(str+i) >= '0' && *(str+i) <= '9'; i++);
 return i;
};

// writing string to the output
void str_write(const char *str)
{
  for( int i = 0; *(str+i) != '\0'; i++ ) write(1, str+i, 1);
};

// writing character to the output
void char_write(const int count, const char str)
{
  for( int i = 0; i < count; i++) write(1, &str, 1);
};

// formatting data
int format_data(const char* format, va_list* args){
  int count = 0;
  int skip = 0;
  int len = 0;
  char *lexeme = NULL;
  switch(*format)
  {
    case '%':
      write(1, "%", 1);
      return 1;
    case 'd':
      str_write(my_itoa(va_arg(*args, int)));
      return 1;
    case 's':
      str_write(va_arg(*args, char*));
      return 1;
    case '0':
      count = my_atoi(format + 1);
      skip = counter(format + 1);
      if( format[skip+1] == 's' ) lexeme = va_arg(*args, char*);
      else lexeme = my_itoa(va_arg(*args, int));
      len = my_strlen(lexeme);
      char_write(count - len, '0');
      str_write(lexeme);
      return skip + 2;
    default:
      count = my_atoi(format);
      skip = counter(format);
      if( format[skip] == 's' ) lexeme = va_arg(*args, char*);
      else lexeme = my_itoa(va_arg(*args, int));
      len = my_strlen(lexeme);
      char_write(count - len, ' ');
      str_write(lexeme);
      return skip + 1;
  }
  return 0;
};

// main function
int my_printf(const char *format, ...) {
  va_list args;
  va_start(args, format);
  int i = 0;
  do {
    if( format[i] != '%' ) {
      write(1, format+i, 1);
      i++;
    } else {
      i+=format_data(format+i+1, &args)+1;
    }
  } while (format[i] != '\0');
  return 0;
}
