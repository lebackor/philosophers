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
	t_philo	*p;

	p = (t_philo *)pol;
	if (p->tg->nb_philos == 1)
		return (one_philo(p));
	if (p->number % 2)
		usleep((p->tg->time_to_eat * 1000) * 0.5);
	while (is_meal(p) == 0 && is_dead(p) == 0 && is_print(p) == 0)
	{
		pthread_mutex_lock(&p->next->mutex);
		print((get_time() - p->tg->current_time), p, FORK);
		pthread_mutex_lock(&p->mutex);
		print((get_time() - p->tg->current_time), p, FORK);
		increase_meal(p);
		print((get_time() - p->tg->current_time), p, "is eating");
		usleep(p->tg->time_to_eat * 1000);
		pthread_mutex_unlock(&p->mutex);
		pthread_mutex_unlock(&p->next->mutex);
		print((get_time() - p->tg->current_time), p, "is sleeping");
		usleep(p->tg->time_to_sleep * 1000);
		print((get_time() - p->tg->current_time), p, "is thinking");
	}
	return (NULL);
}

void	print(long long time, t_philo *p, char *str)
{
	pthread_mutex_lock(&p->tg->canprint);
	if (p->tg->can_print != 1)
	{
		pthread_mutex_lock(&p->tg->print);
		ft_putstr("[");
		ft_putnbr(time);
		ft_putstr("] ");
		ft_putnbr(p->number);
		ft_putstr(" ");
		ft_putstr(str);
		write(1, "\n", 1);
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

void	ft_putnbr(int nb)
{
	if (nb < 0)
	{
		nb = -nb;
	}
	if (nb >= 10)
	{
		ft_putnbr(nb / 10);
		ft_putnbr(nb % 10);
	}
	else
		ft_putchar(nb + '0');
}
