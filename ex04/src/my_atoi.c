int	my_atoi(char *ntpr)
{
	int i;
	int neg;
	int num;

	i = 0;
	neg = 0;
	num = 0;
	while (ntpr[i] == ' ' || (ntpr[i] >= '\t' && ntpr[i] <= '\r'))
		i++;
	if (ntpr[i] == '-')
		neg = 1;
	if (ntpr[i] == '-' || ntpr[i] == '+')
		i++;
	while (ntpr[i] >= '0' && ntpr[i] <= '9')
	{
		num = num * 10;
		num = num + ((int)ntpr[i] - '0');
		i++;
	}
	if (neg == 1)
		return (-num);
	else
		return (num);
}