#include <stdarg.h>
#include <stdio.h>
int my_printf(const char *format, ...)
{
  va_list lst;
  va_start (lst, format);
  int res = vfprintf (stdout, format, lst);
  va_end (lst);
  return res;
}
