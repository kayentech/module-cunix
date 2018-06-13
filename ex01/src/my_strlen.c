unsigned int my_strlen(char *s){
	unsigned int i;
	for ( i=0 ; s[i] != '\0' ; i++ ) ;
	return i;
}
