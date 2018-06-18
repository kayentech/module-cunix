int my_puts(const char *str)
{
  char c='\0';
while(c = *str++)
putchar(c);
putchar('\n');
}
