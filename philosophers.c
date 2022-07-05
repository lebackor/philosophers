#include "philosophers.h"

void    *routine(void *pol)
{
    t_philo *philo;

    philo = (t_philo *)pol;
    philo->current_time = get_time();
    pthread_mutex_lock(&philo->tg->meal);
    philo->time_of_last_meal = get_time();
    pthread_mutex_unlock(&philo->tg->meal);
    if (philo->number % 2 == 0)
        ft_usleep2(philo->time_to_eat / 10, philo);
    while (is_meal(philo) == 0)
    {
        pthread_mutex_lock(&philo->mutex);
        print((get_time() - philo->current_time), philo, "me has taken fork");
        pthread_mutex_lock(&philo->next->mutex);
        print((get_time() - philo->current_time), philo, "has taken fork");
        pthread_mutex_lock(&philo->tg->meal);
        philo->time_of_last_meal = get_time();
        philo->meal++;
        pthread_mutex_unlock(&philo->tg->meal);
        print((get_time() - philo->current_time), philo, "is eating");
        ft_usleep2(philo->time_to_eat, philo);
         pthread_mutex_unlock(&philo->mutex);
        pthread_mutex_unlock(&philo->next->mutex);
        print((get_time() - philo->current_time), philo, "is sleeping");
        ft_usleep2(philo->tg->time_to_sleep, philo);
        print((get_time() - philo->current_time), philo, "is thinking");
    }
    return (NULL);
}
void    *routine1(void *pol)
{
    t_philo *philo;

    philo = (t_philo *)pol;
    if (philo->number % 2 == 0)
        ft_usleep2(philo->time_to_eat / 10, philo);
    while (is_meal(philo) == 0)
    {
        pthread_mutex_lock(&philo->next->mutex);
        print((get_time() - philo->current_time), philo, "has taken fork");
        pthread_mutex_lock(&philo->mutex);
        print((get_time() - philo->current_time), philo, "has taken fork");
        pthread_mutex_lock(&philo->tg->meal);
        philo->time_of_last_meal = get_time();
        philo->meal++;
        pthread_mutex_unlock(&philo->tg->meal);
        print((get_time() - philo->current_time), philo, "is eating");
        ft_usleep2(philo->time_to_eat, philo);
        pthread_mutex_unlock(&philo->next->mutex);
        pthread_mutex_unlock(&philo->mutex);
        print((get_time() - philo->current_time), philo, "is sleeping");
        ft_usleep2(philo->tg->time_to_sleep, philo);
        print((get_time() - philo->current_time), philo, "is thinking");
    }
    return (NULL);
}
void ft_thread(t_philo *p)
{
    t_philo *tmp;
    int i;

    i = 1;
    tmp = p;
    p->tg->current_time = get_time();
    while (i <= p->tg->nb_philos)
    {
        if (i == p->tg->nb_philos)
            pthread_create((&tmp->content), NULL, routine1, tmp);
        else
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
    ft_death(p);
    ft_threadjoin(p);
    return ;
}

int main(int ac, char **av)
{
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
    pthread_mutex_init((&philos->meal), NULL);
    pthread_mutex_init((&philos->canprint), NULL);
    put_philo(p, philos);
    mutex_destroy(p);
    ft_clean(p, philos);
    return (0);
}
