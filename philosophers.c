#include "philosophers.h"

void    *routine(void *pol)
{
    t_philo *philo;


    philo = (t_philo *)pol;
    //print(info, philo, "xd\n");
/*    while (is_dead(philo) == 0 && is_meal(philo) == 0)
  //  {
        //philo->time = (get_time() - philo->tg->current_time) ;
        philo->time = 0;
        printf("[%lld] %d is thinking\n", philo->time , philo->number);
        pthread_mutex_lock(&philo->mutex);
        pthread_mutex_lock(&philo->next->mutex);
      //  pthread_mutex_lock(&philo->tg->print);
        printf("[%lld] %d is eating\n",philo->time , philo->number);
        philo->meal++;
        usleep(philo->tg->time_to_eat);
        //pthread_mutex_unlock(&philo->tg->print);
        pthread_mutex_unlock(&philo->next->mutex);
        pthread_mutex_unlock(&philo->mutex);
        printf("[%lld] %d is sleeping\n", philo->time , philo->number);
        usleep(philo->tg->time_to_sleep);
        printf("[%lld] %d is thinking\n", philo->time , philo->number);
*/
   // }
    return (NULL);
}

void ft_thread(t_philo *p)
{
    t_philo *tmp;
    int i;

    i = 1;
    tmp = p;
    while (i <= p->tg->nb_philos)
    {
       pthread_create((&tmp->content), NULL, routine, tmp); 
       tmp = tmp->next; 
       i++;
    }
}


void ft_threadjoin(t_philo *p)
{
    t_philo *tmp;
    int i;

    tmp = p;
    i = 1;
    while (i <= p->tg->nb_philos)
    {
       pthread_join(tmp->content, NULL);
        printf("%d ok join\n", tmp->number);
       tmp = tmp->next; 
       i++;
    }
   // printf("%d\n", p->nb_philos);
    return ;
}

void put_philo(t_philo *p, t_info *philo)
{

    t_philo *tmp;

    while (philo->i++ < philo->nb_philos)
        ft_addback(p, philo, philo->i);
    tmp = p;
    while (tmp->next != NULL)
        tmp = tmp->next;
    tmp->next = p;
    ft_thread(p);
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
	else
        philos->number_of_times_each_philosopher_must_eat = -1;
    pthread_mutex_init((&philos->print), NULL);
    philos->current_time = get_time();
    put_philo(p, philos);
    mutex_destroy(p);
    //printf("%d\n", p->t);
    return (0);
}