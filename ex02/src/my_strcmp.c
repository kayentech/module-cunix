int my_strcmp(char *str1, char *str2) {
  while (*str1 != '\0') {
    if (*str2 == '\0')
     return 1;
    if (*str1 > *str2)
      return 1;
    if (*str2 > *str1)
      return -1;
    str2++;
    str1++;
  }
  if (*str2 != '\0')
    return -1;
  return 0;
}