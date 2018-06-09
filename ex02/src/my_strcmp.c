char *my_strcpy(char *dest, const char *src) {
  int i = 0;

  for (i = 0; src[i] != '\0'; i++)
    dest[i] = src[i];

  while(dest[i] != '\0') dest[i] = '\0';

  return dest;
}
