int my_atoi(const char *nptr) {
  int i = 0;
  char minus = 0;

  if (*nptr == '-') {
    nptr++;
    minus = 1;
  }
  while (*nptr != '\0') {
    if (*nptr >= '0' && *nptr <= '9') {
      i *= 10;
      i += *nptr - '0';
    }
    else {
      break;
    }
    nptr++;
  }

  return (minus)? i*=-1 : i;
}