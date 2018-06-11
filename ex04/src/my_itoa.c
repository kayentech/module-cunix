#include <stdlib.h>

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