/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebackor <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 16:26:20 by lebackor          #+#    #+#             */
/*   Updated: 2022/08/01 16:37:23 by lebackor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_death(t_philo *p)
{
	while (p->next && p->tg->nb_philos > 1)
	{
		pthread_mutex_lock(&p->tg->meal);
		if (((((get_time() - p->tg->current_time)
						- (p->time_of_last_meal - p->tg->current_time))
					> p->tg->time_to_die)
				&& p->meal > 0))
		{
			pthread_mutex_lock(&p->tg->candeath);
			p->tg->someoneisdead = 1;
			pthread_mutex_unlock(&p->tg->candeath);
			if (!(p->meal == p->tg->number_of_times_each_philosopher_must_eat))
				print((get_time() - p->tg->current_time), p, "is DEAD");
			pthread_mutex_lock(&p->tg->canprint);
			p->tg->can_print = 1;
			pthread_mutex_unlock(&p->tg->canprint);
			pthread_mutex_unlock(&p->tg->meal);
			return ;
		}
		pthread_mutex_unlock(&p->tg->meal);
		p = p->next;
	}
}
/*
int	check_time(t_philo *p)
{
	long long	time;

	time = 0;
	time = get_time();
	if (((((time 
		- p->tg->current_time)
		- (p->time_of_last_meal - p->tg->current_time)) > p->tg->time_to_die)
		&& p->meal > 0))
		return (1);
	else
		return (0);
}
*/

int	is_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->tg->candeath);
	if (philo->tg->someoneisdead == 0)
	{
		pthread_mutex_unlock(&philo->tg->candeath);
		return (0);
	}
	pthread_mutex_unlock(&philo->tg->candeath);
	return (1);
}

int	is_meal(t_philo *p)
{
	if (p->tg->number_of_times_each_philosopher_must_eat == -1)
		return (0);
	if (p->tg->number_of_times_each_philosopher_must_eat == 0)
		return (1);
	if (p->meal == p->tg->number_of_times_each_philosopher_must_eat)
		return (1);
	return (0);
}
