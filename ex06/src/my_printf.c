#include <stdio.h>
#include <stdarg.h>

int my_printf(const char *format, ...) {
  va_list arg;
  int answer;
  va_start(arg, format);
  answer = vfprintf(stdout, format, arg);
  va_end(arg);
  return answer;
}
