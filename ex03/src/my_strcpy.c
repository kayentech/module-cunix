char *my_strcpy(char *dest, const char *src) {
  char *ptr = dest;
  while(*src != '\0') {
    *ptr = *src;
    ptr++;
    src++;
  }
  *ptr = *src;

  return dest;
}