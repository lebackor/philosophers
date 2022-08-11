/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   liste.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebackor <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 16:39:53 by lebackor          #+#    #+#             */
/*   Updated: 2022/08/01 21:18:46 by lebackor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_philo	*create_liste(t_philo *p)
{
	p = malloc(sizeof(t_philo));
	if (!p)
		return (0);
	p->meal = 0;
	p->time_of_last_meal = 0;
	p->next = NULL;
	return (p);
}

t_philo	*ft_addback(t_philo *p, t_info *philo, int i)
{
	t_philo	*t_pile;

	if (i == 1)
	{
		p->number = 1;
		p->tg = philo;
		pthread_mutex_init((&p->mutex), NULL);
	}
	else
	{
		t_pile = p;
		while (t_pile->next != NULL)
			t_pile = t_pile->next;
		t_pile->next = NULL;
		t_pile->next = create_liste(p);
		if (!t_pile->next)
			return (0);
		t_pile->next->tg = philo;
		t_pile->next->number = t_pile->number + 1;
		pthread_mutex_init((&t_pile->next->mutex), NULL);
		return (t_pile);
	}
	return (p);
}
