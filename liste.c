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
		pthread_create((&p->content), NULL, routine, p);
    	//pthread_join(p->content, NULL);
	}
	else
	{
        t_pile = p;
		while (t_pile->next != NULL)  
			t_pile = t_pile->next;
		t_pile->next = create_liste(p);
		pthread_create((&t_pile->next->content), NULL, routine, p);
    //	pthread_join(t_pile->next->content, NULL);
        return (t_pile);
	}
	return (p);
}