#include "philosophers.h"

void    *routine(void *pol)
{
    printf("x\n");
    (void) pol;
    return NULL;
}

void ft_threadjoin(t_philo *p)
{
    t_philo *tmp;

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


void put_philo(t_philo *p, t_info *philo)
{

    pthread_mutex_init(&p->mutex, NULL);
    while (philo->i++ < philo->nb_philos)
        ft_addback(p);
    ft_threadjoin(p);
    return ;
}

int main(int ac, char **av, char **envp)
{
    (void) envp;
    t_philo *p;
    t_info *philos;
    if (ac != 5 && ac != 6)
        return (printf("Not the good args\n"));
    p = malloc(sizeof(t_philo));
    philos = malloc(sizeof(t_info));
    *p = (t_philo){0};
    *philos = (t_info){0};
    philos->nb_philos = ft_atoi(av[1]);
    philos->time_to_die = ft_atoi(av[2]);
    philos->time_to_eat = ft_atoi(av[3]);
    philos->time_to_sleep = ft_atoi(av[4]);
    if (ac == 6)
        philos->number_of_times_each_philosopher_must_eat = ft_atoi(av[5]);
    put_philo(p, philos);
    //printf("%d\n", p->t);
}