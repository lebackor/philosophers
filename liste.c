#include "philosophers.h"
t_philo	*create_liste(t_philo *p)
{
	p = malloc(sizeof(t_philo));
	p->next = NULL;
	return (p);
}

t_philo	*ft_addback(t_philo *p, t_info *philo, int i)
{
	t_philo	*t_pile;

	if (i == 1)
	{
	//	create_liste(p);
		p->number = 1;
		p->tg = philo;
    	p->current_time = get_time();
		p->time_to_eat = p->tg->time_to_eat;
		pthread_mutex_init((&p->mutex), NULL);
   //     pthread_create((&p->content), NULL, routine, p); 
	}
	else
	{
        t_pile = p;
		while (t_pile->next != NULL)  
			t_pile = t_pile->next;
		t_pile->next = create_liste(p);
		t_pile->next->tg = philo;
		t_pile->next->number = t_pile->number + 1;
		t_pile->next->tg->number_of_times_each_philosopher_must_eat = t_pile->tg->number_of_times_each_philosopher_must_eat; 
    	t_pile->next->current_time = t_pile->current_time;
		t_pile->next->time_to_eat = p->tg->time_to_eat;
		pthread_mutex_init((&t_pile->next->mutex), NULL); 
	//	pthread_create((&t_pile->next->content), NULL, routine, t_pile->next);
		return (t_pile);
	}
	return (p);
}