unsigned int my_strlen(char *str)
{
   unsigned int count =0;
       while(*str!='\0')
       {
         count++;
      str++;
    }
    return count;
   }

