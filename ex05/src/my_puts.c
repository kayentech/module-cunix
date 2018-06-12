unsigned int my_strlen(const char *str) {
  unsigned i;
  for(i = 0; *(str + i) != '\0'; i++);
  return i;
}

int my_puts(const char *s) {
  extern long write(int, const char *, unsigned long);

  write(1, s, my_strlen(s));
  write(1, "\n", 1);
}
