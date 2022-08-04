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
		usleep((philo->tg->time_to_eat * 1000) / 10);
	while (is_meal(philo) == 0 && philo->tg->someoneisdead == 0)
	{
		pthread_mutex_lock(&philo->next->mutex);
		print((get_time() - philo->tg->current_time), philo, "has taken fork");
		pthread_mutex_lock(&philo->mutex);
		print((get_time() - philo->tg->current_time), philo, "has taken fork");
		increase_meal(philo);
		print((get_time() - philo->tg->current_time), philo, "is eating");
		usleep(philo->tg->time_to_eat * 1000);
		pthread_mutex_unlock(&philo->mutex);
		pthread_mutex_unlock(&philo->next->mutex);
		print((get_time() - philo->tg->current_time), philo, "is sleeping");
		usleep(philo->tg->time_to_sleep * 1000);
		print((get_time() - philo->tg->current_time), philo, "is thinking");
	}
	return (NULL);
}
/*
void	ft_usleep2(long long time)
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
}*/

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
	pthread_mutex_destroy(&p->tg->meal);
	pthread_mutex_destroy(&p->tg->canprint);
	pthread_mutex_destroy(&p->tg->candeath);
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
	free(philo);
}
