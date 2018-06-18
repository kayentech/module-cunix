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