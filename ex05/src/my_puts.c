#include <string.h>
int my_puts(const char *s) {
  extern long write(int, const char *, unsigned long);

  write(1, s, strlen(s));
  write(1, "\n", 1);
}