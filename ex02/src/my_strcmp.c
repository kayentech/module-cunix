int my_strcmp(char *str1, char *str2)
{
  while (*str1==*str2){
  if (*str1=='\0'|| *str2=='\0')
   break;
  str1++;
  str2++;
  }
  return *str1-*str2 > 0 ? 1 : *str1-*str2 < 0 ? -1 : 0;
}



