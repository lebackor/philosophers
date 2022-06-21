#include "philosophers.h"

int is_dead(t_philo *p)
{
    
    
    if (p->is_dead == 1)
            return (1);
    
    return (0);
}

int is_meal(t_philo *p)
{
    if (p->tg->number_of_times_each_philosopher_must_eat == -1)
        return (0);
    if (p->tg->number_of_times_each_philosopher_must_eat == 0)
        return (1);
    if (p->meal == p->tg->number_of_times_each_philosopher_must_eat)
        return (1);
    return (0);
}