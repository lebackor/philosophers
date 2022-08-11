/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebackor <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 16:39:25 by lebackor          #+#    #+#             */
/*   Updated: 2022/08/05 19:55:26 by lebackor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*routine(void *pol)
{
	t_philo	*p;

	p = (t_philo *)pol;
	if (p->number % 2 == 0)
		usleep((p->tg->time_to_eat * 1000) * 0.5);
	while (is_meal(p) == 0 && is_dead(p) == 0 && is_print(p) == 0)
	{
		pthread_mutex_lock(&p->mutex);
		print((get_time() - p->tg->current_time), p, FORK);
		pthread_mutex_lock(&p->next->mutex);
		print((get_time() - p->tg->current_time), p, FORK);
		increase_meal(p);
		print((get_time() - p->tg->current_time), p, "is eating");
		usleep(p->tg->time_to_eat * 1000);
		pthread_mutex_unlock(&p->next->mutex);
		pthread_mutex_unlock(&p->mutex);
		print((get_time() - p->tg->current_time), p, "is sleeping");
		usleep(p->tg->time_to_sleep * 1000);
		print((get_time() - p->tg->current_time), p, "is thinking");
	}
	return (NULL);
}

void	ft_thread(t_philo *p)
{
	t_philo	*tmp;
	int		i;

	i = 1;
	tmp = p;
	while (i <= p->tg->nb_philos)
	{
		if (i == p->tg->nb_philos)
		{
			if (pthread_create((&tmp->content), NULL, routine1, tmp) != 0)
				p->tg->can_print = 1;
		}	
		else
		{
			if (pthread_create((&tmp->content), NULL, routine, tmp) != 0)
				p->tg->can_print = 1;
		}
		tmp = tmp->next;
		i++;
	}
}

void	ft_threadjoin(t_philo *p)
{
	t_philo	*tmp;
	int		i;

	tmp = p;
	i = 1;
	while (i <= p->tg->nb_philos)
	{
		pthread_join(tmp->content, NULL);
		tmp = tmp->next;
		i++;
	}
	return ;
}

int	put_philo(t_philo *p, t_info *philo)
{
	t_philo	*tmp;

	while (philo->i++ < philo->nb_philos)
	{
		if (ft_addback(p, philo, philo->i) == 0)
		{
			ft_clean(p, philo);
			return (0);
		}
	}
	tmp = p;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = p;
	ft_thread(p);
	ft_death(p);
	ft_threadjoin(p);
	return (1);
}

int	main(int ac, char **av)
{
	t_philo	*p;
	t_info	*philos;

	if (ac != 5 && ac != 6)
		return (printf("Not the good args\n"));
	p = malloc(sizeof(t_philo));
	if (!p)
		return (0);
	*p = (t_philo){0};
	philos = malloc(sizeof(t_info));
	if (!philos)
		return (0);
	*philos = (t_info){0};
	init_philo(philos, ac, av);
	if (philos->current_time == 0)
		return (0);
	if (put_philo(p, philos) == 0)
		return (printf("Malloc issues\n"));
	mutex_destroy(p);
	ft_clean(p, philos);
	return (0);
}
