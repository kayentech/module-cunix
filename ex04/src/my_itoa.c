#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

char* my_itoa(int nmb) {
	
	// if number is 0
	if(nmb == 0) {
		char* none = malloc(sizeof(char));
		*none = '0';
		return none;
	}
	
	bool sign = false;
	
	// if number is negative
	if(nmb < 0) {
		sign = true;
		nmb*=-1;
	}

	int i = log10((double) abs(nmb)); // take number of charecters
	char* dest = malloc(i);
	while(nmb > 0){
		dest[i] = (nmb % 10) + '0';
		nmb/=10;
		i-=1;
	}
	
	// adding '-' if number is negative
	if(sign) {
		for( int j = strlen(dest) - 1; j>=0 ; j--)
			dest[j+1] = dest[j];
		dest[0] = '-';
	}
	dest[i] = '\0';
	return dest;
}
