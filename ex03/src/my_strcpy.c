char *my_strcpy(char *dest, const char *src){
	int i=0;
	for(;(dest[i] = src[i]) != '\0';i++);
	dest[i] = '\0';
	return dest;
}
