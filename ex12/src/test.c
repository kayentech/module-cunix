#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "test.h"

int   test_small()
{
	char *foo = (char *)halloc(0);
	assert( foo >  0x0000000000000001);
	free(foo);
	assert(foo >  0x0000000000000001);
	foo = halloc(10000000000000000000);
	assert(foo == NULL);
	free(foo);
	assert(foo == NULL);
	return 0;
}

int           test_long()
{
	int **a = (int **)halloc(sizeof(int) * 10000);
	for (int i = 0; i < 1000; i++)
	{
		int *tmp = (int *)halloc(sizeof(int));
		*tmp = i;
		a[i] = tmp;
	}

	for (int i = 0; i < 1000; i++)
		free(a[i]);
  free(a);
	return 0;
}



int   main(int argc, char *argv[])
{
	test_small();
	test_long();
	return 0;
}
