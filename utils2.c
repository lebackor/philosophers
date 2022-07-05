#include "philosophers.h"


void    ft_usleep(long long time)
{ 
    long long   start;
    long long   current; 

    start = get_time();
    while (1)
    {
        current = get_time();
        if (current - start > time)
            return ;
        else if (current - start > 1000)
            usleep(100);
        else
            usleep(1);
    }
}

void    ft_usleep2(long long time, t_philo *p)
{ 
    long long   start;
    long long   current;

    (void)p;
    start = get_time();
    while (1)
    {
        current = get_time() - start;
        if (current >= time)
            return ;
        if (time - current >= 1000)
            usleep(100);
        else
            usleep((time - current) / 10);
    }
}

void print(long long time, t_philo *p, char *str)
{
    pthread_mutex_lock(&p->tg->canprint);
    if (p->tg->can_print != 1)
    {
        pthread_mutex_lock(&p->tg->print);
        printf("[%lld] %d %s\n", time, p->number, str);
        pthread_mutex_unlock(&p->tg->print);
    }
    pthread_mutex_unlock(&p->tg->canprint);
    return ;
}

void mutex_destroy(t_philo *p)
{
    t_philo *tmp;
    int i;

    i = 0;
    tmp = p;
    pthread_mutex_destroy(&p->tg->print);
    while (i < p->tg->nb_philos)
    {
        pthread_mutex_destroy(&tmp->mutex);
        tmp = tmp->next;
        i++;
    }
}

void ft_clean(t_philo *p, t_info *philo)
{
    t_philo *tmp;
    int i;

    i = 0;
    while (i < philo->nb_philos)
    {
        tmp = p;
        p = p->next;
        if (tmp)    
            free(tmp);
        i++;
    }
    if (philo)
        free(philo);
}
