#include "test.h"


int my_atoi(const char *nptr){
  int i=0;
  int sign=1;
  int f = 1;
  do{
    if(*nptr=='-' && f==1){
      sign=-1;
    }else if(*nptr=='0'){
      i=i*10;
    }else if(*nptr=='1'){
      i=(i*10)+1;
    }else if(*nptr=='2'){
      i=(i*10)+2;
    }else if(*nptr=='3'){
      i=(i*10)+3;
    }else if(*nptr=='4'){
      i=(i*10)+4;
    }else if(*nptr=='5'){
      i=(i*10)+5;
    }else if(*nptr=='6'){
      i=(i*10)+6;
    }else if(*nptr=='7'){
      i=(i*10)+7;
    }else if(*nptr=='8'){
      i=(i*10)+8;
    }else if(*nptr=='9'){
      i=(i*10)+9;
    } else{return i*sign;};
    f=0;
  } while(*nptr++ != '\0');
  return i*sign;
};







