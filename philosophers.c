#include "philosophers.h"

void    *routine(void *pol)
{
    t_philo *philo;

    philo = (t_philo *)pol;
   // while (is_dead(philo) == 0)
   // {

        pthread_mutex_lock(&philo->mutex);
      //  pthread_mutex_lock(&philo->next->mutex);
        printf("%d is eating\n",philo->number);
        pthread_mutex_unlock(&philo->mutex);
        //pthread_mutex_unlock(&philo->next->mutex);
       // usleep(50000);
    
   // }
    return (NULL);
}

void ft_threadjoin(t_philo *p)
{
    t_philo *tmp;
    int i;

    tmp = p;
    i = 0;
    while (i < p->nb_philos)
    {
       pthread_join(tmp->content, NULL);
       tmp = tmp->next; 
       i++;
    }
    printf("%d\n", i);
    return ;
}
/*
void ft_thread(t_philo *p)
{
    t_philo *tmp;
    int i;
    tmp = p;
    i = 0;

    while (i < p->nb_philos)
    {
	    pthread_mutex_init((&tmp->mutex), NULL); 
        pthread_create((&tmp->content), NULL, routine, p);
        tmp = tmp->next;

        i++;
    }
}*/

void put_philo(t_philo *p, t_info *philo)
{

    t_philo *tmp;

    while (philo->i++ < philo->nb_philos)
        ft_addback(p);
    tmp = p;
    while (tmp->next != NULL)
        tmp = tmp->next;
    tmp->next = p;
    p->nb_philos = philo->nb_philos;
   // ft_thread(p);
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