/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebackor <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 16:39:17 by lebackor          #+#    #+#             */
/*   Updated: 2022/08/01 16:42:57 by lebackor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*one_philo(t_philo *philo)
{
	print((get_time() - philo->tg->current_time), philo, "has taken fork");
	ft_usleep2(philo->tg->time_to_die);
	print((get_time() - philo->tg->current_time), philo, "is DEAD");
	return (NULL);
}

int	is_number(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((str[i] < '0' && str[i] != '-') || (str[i] > '9' && str[i] != '-'))
			return (1);
		i++;
	}
	return (0);
}

int	init_philo(t_info *philos, int ac, char **av)
{
	if ((is_number(av[1]) == 1) || (is_number(av[2]) == 1)
	|| (is_number(av[3]) == 1) || (is_number(av[4]) == 1))
		return (printf("Parsing error, not int\n"));
	philos->nb_philos = ft_atoi(av[1]);
	philos->time_to_die = ft_atoi(av[2]);
	philos->time_to_eat = ft_atoi(av[3]);
	philos->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		philos->number_of_times_each_philosopher_must_eat = ft_atoi(av[5]);
	else
		philos->number_of_times_each_philosopher_must_eat = -1;
	if ((philos->nb_philos < 1))
		return (printf("Philosophers error\n"));
	if (philos->number_of_times_each_philosopher_must_eat < 1 && ac == 6)
		return (printf("Meal error\n"));
	if ((philos->time_to_die < 0) || (philos->time_to_eat < 0)
	|| (philos->time_to_sleep < 0))
		return (printf("Time error\n"));
	pthread_mutex_init((&philos->print), NULL);
	pthread_mutex_init((&philos->meal), NULL);
	pthread_mutex_init((&philos->canprint), NULL);
	pthread_mutex_init((&philos->candeath), NULL);
	philos->current_time = get_time();
	return (1);
}
