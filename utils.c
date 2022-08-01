/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebackor <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 16:39:39 by lebackor          #+#    #+#             */
/*   Updated: 2022/08/01 16:39:41 by lebackor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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

long long get_time(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return (((tv.tv_sec) * 1000) + ((tv.tv_usec) / 1000));
}

void increase_meal(t_philo *philo)
{
    pthread_mutex_lock(&philo->tg->meal);
    philo->time_of_last_meal = get_time();
    philo->meal++;
    pthread_mutex_unlock(&philo->tg->meal);
}
