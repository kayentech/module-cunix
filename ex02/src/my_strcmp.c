int my_strcmp(char* str1, char* str2) {
	while (*str1 == *str2 && *str1++ | *str2++);
	int i = *str1 - *str2;
	return i > 0 ? 1 : i < 0 ? -1 : 0;
}

