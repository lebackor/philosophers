#include "philosophers.h"

int is_dead(t_philo *p)
{
    if (get_time() - p->time_of_last_meal > 1000 && p->meal > 0)
    {
        pthread_mutex_lock(&p->tg->print);
        printf("[%lld] %d is DEAD\n", get_time() - p->tg->current_time, p->number);
        pthread_mutex_unlock(&p->tg->print);
        return (1);
    }
   // printf("%lld\n", get_time() - p->time_of_last_meal);
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