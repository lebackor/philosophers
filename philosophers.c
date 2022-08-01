/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebackor <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 16:39:25 by lebackor          #+#    #+#             */
/*   Updated: 2022/08/01 19:54:25 by lebackor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
// maybe change ftusleep2 en real usleep 
void	*routine(void *pol)
{
	t_philo	*philo;

	philo = (t_philo *)pol;
	pthread_mutex_lock(&philo->tg->meal);
	philo->time_of_last_meal = get_time();
	pthread_mutex_unlock(&philo->tg->meal);
	if (philo->number % 2 == 0)
		ft_usleep2(philo->time_to_eat / 10, philo);
	while (is_meal(philo) == 0 && philo->tg->someoneisdead == 0)
	{
		pthread_mutex_lock(&philo->mutex);
		print((get_time() - philo->tg->current_time), philo, "has taken fork");
		pthread_mutex_lock(&philo->next->mutex);
		print((get_time() - philo->tg->current_time), philo, "has taken fork");
		increase_meal(philo);
		print((get_time() - philo->tg->current_time), philo, "is eating");
		ft_usleep2(philo->time_to_eat, philo);
		pthread_mutex_unlock(&philo->next->mutex);
		pthread_mutex_unlock(&philo->mutex);
		print((get_time() - philo->tg->current_time), philo, "is sleeping");
		ft_usleep2(philo->tg->time_to_sleep, philo);
		print((get_time() - philo->tg->current_time), philo, "is thinking");
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
			pthread_create((&tmp->content), NULL, routine1, tmp);
		else
			pthread_create((&tmp->content), NULL, routine, tmp);
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

void	put_philo(t_philo *p, t_info *philo)
{
	t_philo	*tmp;

	while (philo->i++ < philo->nb_philos)
		ft_addback(p, philo, philo->i);
	tmp = p;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = p;
	p->tg->current_time = get_time();
	ft_thread(p);
	ft_death(p);
	ft_threadjoin(p);
	return ;
}

int	main(int ac, char **av)
{
	t_philo	*p;
	t_info	*philos;

	if (ac != 5 && ac != 6)
		return (printf("Not the good args\n"));
	if (ft_atoi(av[1]) < 1)
		return (printf("No Philosophers\n"));
	p = malloc(sizeof(t_philo));
	*p = (t_philo){0};
	philos = malloc(sizeof(t_info));
	*philos = (t_info){0};
	init_philo(philos, ac, av);
	put_philo(p, philos);
	mutex_destroy(p);
	ft_clean(p, philos);
	return (0);
}
