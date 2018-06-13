#include <stdbool.h>
int my_atoi(const char *nptr){
	int val = 0;
	bool sign = false;
	if(*nptr == '-') {
		sign = true;
		++nptr;
	}
	while(*nptr >= '0' && *nptr <= '9') {
		val = (val * 10) + (*nptr - '0');
		++nptr;
	}
	return sign ? -val : val;
}
