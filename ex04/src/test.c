#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "test.h"

int   test_small()
{
  assert(my_atoi("0") == 0);
  assert(my_atoi("-0") == 0);
  assert(my_atoi("-1") == -1);
  assert(my_atoi("42") == 42);
  assert(my_atoi("-42") == -42);
  assert(my_atoi("1k") == 1);
}

int           test_long()
{
  assert(my_atoi("123456789") == 123456789);
  assert(my_atoi("2147483647") == 2147483647);
  assert(my_atoi("-2147483648") == -2147483648);
  assert(my_atoi("4294967296") == 0);
  assert(my_atoi("4294967298") == 2);
  assert(my_atoi("ABC") == 0);
  assert(my_atoi("0") == atoi("0"));
}

int           test_verif()
{
  assert(atoi("0") == 0);
  assert(atoi("-0") == 0);
  assert(atoi("-1") == -1);
  assert(atoi("42") == 42);
  assert(atoi("-42") == -42);
  assert(atoi("1k") == 1);
  assert(atoi("123456789") == 123456789);
  assert(atoi("2147483647") == 2147483647);
  assert(atoi("-2147483648") == -2147483648);
  assert(atoi("4294967296") == 0);
  assert(atoi("4294967298") == 2);
  assert(atoi("ABC") == 0);
  assert(atoi("1234QWERTY1234") == 1234);
}

int     test_itoa()
{

  assert(strcmp(my_itoa(0), "0") == 0);
  assert(strcmp(my_itoa(1), "1") == 0);
  assert(strcmp(my_itoa(32), "32") == 0);
  assert(strcmp(my_itoa(12345678), "12345678") == 0);
  assert(strcmp(my_itoa(-34), "-34") == 0);
  assert(strcmp(my_itoa(-12345678), "-12345678") == 0);
  assert(strcmp(my_itoa(-1234567890), "-1234567890") == 0);
}
int   main(int argc, char *argv[])
{
  test_small();
  test_long();
  test_verif();
  test_itoa();
  return(0);
}
