#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>

int my_atoi(const char* nptr) {
	int res = 0;
	while (isspace((unsigned char)*nptr))
		nptr++;
	char sign = *nptr;
	if (*nptr == '-' || *nptr == '+')
		nptr++;
	while (isdigit((unsigned char)*nptr))
		res = res * 10 - (*nptr++ - '0');
	if (sign != '-')
		res = -res;
	return res;
}

unsigned int my_strlen(char *str)
{
	int i = 0;
	while (*str++)
		i++;
	return i;
}

char *my_itoa(int i)
{
	int j = 1;
	static char buf[sizeof(int) + 2];
	char *res = buf + sizeof(int) + 1;
	do {
		*--res = '0' + (abs(i / j) % 10);
		j *= 10;
	} while (i / j);
	if (i < 0) *--res = '-';
	return res;
}

void my_printf(const char *format, ...)
{
	int total, count = 0, arg1, size, i, loop_count, whitespases = 0, zero_chars = 0;
	char token, *arg3, *tmp, temp;
	va_list ap;
	char zr = '0';
	char ws = ' ';
	va_start(ap, format);
	while (*format != '\0')
	{
		if (*format == '%')
		{
			if (*(format + 1) == '0')
			{
				zero_chars = 1;
				format++;
			}
			else zero_chars = 0;
			if (*(format + 1) >= '1' && *(format + 1) <= '9')
			{
				while ((temp = *(++format)) >= '0' && temp <= '9')
					count++;
				tmp = (char*)malloc(count * sizeof(char));
				format -= count;
				for (i = 0; i < count; i++)
					*(tmp + i) = *(format++);
				whitespases = my_atoi(tmp);
				format--;
				count = 0;
			}
			token = *(++format);
			switch (token)
			{
			case 'd':
				arg3 = my_itoa(va_arg(ap, int));
				size = my_strlen(arg3);
				loop_count = whitespases - size;
				if (!zero_chars)
					for (i = 0; i < loop_count; i++)
						write(1, &ws, sizeof(char));
				else
					if (zero_chars)
						for (i = 0; i < loop_count; i++)
							write(1, &zr, sizeof(char));
				for (i = 0; i < size; i++)
					write(1, &arg3[i], sizeof(char));
				break;

			case '%':
				write(1, &token, sizeof(token));
				break;
			case 's':
				arg3 = va_arg(ap, char *);
				size = my_strlen(arg3);
				loop_count = whitespases - size;
				if (!zero_chars)
					for (i = 0; i < loop_count; i++)
						write(1, &ws, sizeof(char));
				else
					if (zero_chars)
						for (i = 0; i < loop_count; i++)
							write(1, &zr, sizeof(char));
				for (i = 0; i < size; i++)
					write(1, &arg3[i], sizeof(char));
				break;
			}
		}
		else write(1, &(*format), sizeof(*format));
		format++;
	}
}











