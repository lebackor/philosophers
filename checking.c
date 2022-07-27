#include "philosophers.h"

int is_dead(t_philo *p)
{
    if ((((get_time() - p->time_of_last_meal) > p->tg->time_to_die) && p->meal > 0))
    {
        p->is_dead = 1;
      //  pthread_detach(p->content);
       // pthread_mutex_lock(&p->tg->print);
       // printf("[%lld] %d is DEAD\n", get_time() - p->tg->current_time, p->number);
       // pthread_mutex_unlock(&p->tg->print);
        return (1);
    }
 //   printf("%lld\n", (get_time() - p->tg->current_time) - p->time_of_last_meal);
    //printf("%lld\n", p->time_of_last_meal);
    if (p->is_dead == 1)
            return (1);
    
    return (0);
}
/*
t_philo get_index(t_philo p, int index)
{
    while (index >= 0)
    {
        p->
    }
}*/

void    ft_death(t_philo *p)
{
    while (p->next && p->tg->nb_philos > 1)
    {
        pthread_mutex_lock(&p->tg->meal);
        if (((((get_time() - p->current_time) - (p->time_of_last_meal - p->current_time)) > p->tg->time_to_die) && p->meal > 0))
        {
            print((get_time() - p->current_time), p, "is DEAD");
            p->is_dead = 1;
            p->tg->someoneisdead = 1;
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
