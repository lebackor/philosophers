/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebackor <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 16:39:44 by lebackor          #+#    #+#             */
/*   Updated: 2022/08/01 16:39:47 by lebackor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*routine1(void *pol)
{
	t_philo	*philo;

	philo = (t_philo *)pol;
	if (philo->tg->nb_philos == 1)
		return (one_philo(philo));
	if (philo->number % 2 == 0)
		ft_usleep2(philo->time_to_eat / 10, philo);
	while (is_meal(philo) == 0 && philo->tg->someoneisdead == 0)
	{
		pthread_mutex_lock(&philo->next->mutex);
		print((get_time() - philo->tg->current_time), philo, "has taken fork");
		pthread_mutex_lock(&philo->mutex);
		print((get_time() - philo->tg->current_time), philo, "has taken fork");
		increase_meal(philo);
		print((get_time() - philo->tg->current_time), philo, "is eating");
		ft_usleep2(philo->time_to_eat, philo);
		pthread_mutex_unlock(&philo->mutex);
		pthread_mutex_unlock(&philo->next->mutex);
		print((get_time() - philo->tg->current_time), philo, "is sleeping");
		ft_usleep2(philo->tg->time_to_sleep, philo);
		print((get_time() - philo->tg->current_time), philo, "is thinking");
	}
	return (NULL);
}

void	ft_usleep2(long long time, t_philo *p)
{
	long long	start;
	long long	current;

	start = get_time();
	while (1)
	{
		current = get_time() - start;
		if (current >= time)
			return ;
		if (time - current >= 1000)
			usleep(100);
		else
			usleep((time - current) / 10);
	}
}

void	print(long long time, t_philo *p, char *str)
{
	pthread_mutex_lock(&p->tg->canprint);
	if (p->tg->can_print != 1)
	{
		pthread_mutex_lock(&p->tg->print);
		printf("[%lld] %d %s\n", time, p->number, str);
		pthread_mutex_unlock(&p->tg->print);
	}
	pthread_mutex_unlock(&p->tg->canprint);
	return ;
}

void	mutex_destroy(t_philo *p)
{
	t_philo	*tmp;
	int		i;

	i = 0;
	tmp = p;
	pthread_mutex_destroy(&p->tg->print);
	while (i < p->tg->nb_philos)
	{
		pthread_mutex_destroy(&tmp->mutex);
		tmp = tmp->next;
		i++;
	}
}

void	ft_clean(t_philo *p, t_info *philo)
{
	t_philo	*tmp;
	int		i;

	i = 0;
	while (i < philo->nb_philos)
	{
		tmp = p;
		p = p->next;
		if (tmp)
			free(tmp);
		i++;
	}
	if (philo)
		free(philo);
}
