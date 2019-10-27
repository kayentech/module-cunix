
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "../include/test.h"

void   test_small()
{
  assert(my_strlen("") == 0);
  assert(my_strlen("0") == 1);
  assert(my_strlen("A") == 1);
  assert(my_strlen("AB") == 2);
  assert(my_strlen("ABC") == 3);
}

void   test_long()
{
  assert(my_strlen("uhohthoa1iath6Vagae8ahchoiyie0voo1Chie7iesh2eed6ua9") == 51);
  assert(my_strlen("luuch6iev0uuGhahwa6kochuiga3aok3aebeigii1xee9cue6ooz") == 52);
  assert(my_strlen("") == 0);
  assert(my_strlen("ohlohGee3wae ohlohGee3wae") == 25);
  assert(my_strlen("Ro1miesiebo2AiShohs9TieghakooP3v") == 32);
  assert(my_strlen("") == 0);
  assert(my_strlen("hae7xuTahfae2vai7sae6pu0chaGhoop2\n") == 34);
}

void   test_very()
{
  assert(my_strlen("ohnema2Fohweicho9AiShoh9reih9thae7eP7ooquohce0iechix8AhKaizu2Eebais6eex5phi7Noosohsh3AiWaequo1yaethoo9Vohghipainaed5Choh5ae") == 123);
  assert(my_strlen("OHNEMA2FOHWEICHO9AISHOH9REIH9THAE7EP7OOQUOHCE0IECHIX8AHKAIZU2EEBAIS6EEX5PHI7NOOSOHSH3AIWAEQUO1YAETHOO9VOHGHIPAINAED5CHOH5AE") == 123);
  assert(my_strlen("ahgh9Uw2aipeishohv8eesh6quai5xiobeehae5zei4peth9loZ3aiqu0oonaNaiJeiwoo4thaeKoogu5ees5razie9di8uChohneighaet9Ohcohsheu6opeix") == 123);
  assert(my_strlen("leenahrohing2Ye8hohghiu7ShoohaeT5Lie3aehoo6feeceaJ5aiKooph3eeHo5ieroghoh7Shie5Quaiho7lathievoePheivi4uegi1feibei2OowuoCheuj") == 123);
}

void   main()
{
  test_small();
  test_long();
  test_very();
  return(0);
}
