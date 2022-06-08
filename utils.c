int	ft_atoi(const char *str)
{
	int			i;
	long long	nb;
	int			sign;

	i = 0;
	nb = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		if (nb * sign > 2147483647)
			return (-1);
		else if (nb * sign < -2147483648)
			return (0);
		nb = nb * 10 + str[i] - 48;
		i++;
	}
	return (nb * sign);
}