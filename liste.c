#include "philosophers.h"
t_philo	*create_liste(t_philo *p)
{
	p = malloc(sizeof(t_philo));
	p->next = NULL;
	return (p);
}
t_philo	*ft_addback(t_philo *p)
{
	t_philo	*t_pile;

	if (!(p->content))
	{
		create_liste(p);
		p->number = 1;
		pthread_mutex_init((&p->mutex), NULL);
        pthread_create((&p->content), NULL, routine, p); 
	}
	else
	{
        t_pile = p;
		while (t_pile->next != NULL)  
			t_pile = t_pile->next;
		t_pile->next = create_liste(p);
		t_pile->next->number = t_pile->number + 1;
		pthread_mutex_init((&t_pile->next->mutex), NULL); 
		pthread_create((&t_pile->next->content), NULL, routine, p);
		return (t_pile);
	}
	return (p);
}