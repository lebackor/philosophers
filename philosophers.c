#include "philosophers.h"

void    *routine(void *pol)
{
    t_env *p;
    
    p = (t_env *)pol;
    p->thread = p->thread + 1;
    printf("timestamps %d is thinking\n", p->thread);
    if (pthread_mutex_lock(&p->mutex) == 0 && p->fork > 1)
    {
        printf("timestamps %d is eating\n", p->thread);
        usleep(p->time_to_eat);
        printf("timestamps %d is sleeping\n", p->thread);
        usleep(p->time_to_sleep);
        pthread_mutex_unlock(&p->mutex);
    }
    else
    {
        usleep(5000);
    }
    return NULL;
}

void ft_threadjoin(t_env *p)
{
    t_env *tmp;

    tmp = p;
    while (tmp->next != NULL)
    {
       pthread_join(tmp->content, NULL);
       tmp = tmp->next; 
    }
    if (tmp->content)
        pthread_join(tmp->content, NULL);
    return ;
}


void put_philo(t_env *p)
{

    p->fork = p->nb_philos;
    p->thread = 0;
    pthread_mutex_init(&p->mutex, NULL);
    while (p->i++ < p->nb_philos)
        ft_addback(p);
    ft_threadjoin(p);
    return ;
}

int main(int ac, char **av, char **envp)
{
    (void) envp;
    t_env *p;

    if (ac != 5)
        return (printf("Not the good args\n"));
    p = malloc(sizeof(t_env));
    *p = (t_env){0};
    p->nb_philos = ft_atoi(av[1]);
    p->time_to_die = ft_atoi(av[2]);
    p->time_to_eat = ft_atoi(av[3]);
    p->time_to_sleep = ft_atoi(av[4]);
    put_philo(p);
    //printf("%d\n", p->t);
}