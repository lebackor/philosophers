#include "philosophers.h"

void    *routine(void *pol)
{
    t_env *p;
    
    p = (t_env *)pol;
    pthread_mutex_lock(&p->mutex);
    while (p->t < 50000000)
        p->t++;
   pthread_mutex_unlock(&p->mutex);
    return NULL;
}

void put_philo(t_env *p)
{

    pthread_mutex_init(&p->mutex, NULL);
    while (p->i++ < p->nb_philos)
        ft_addback(p);
    return ;
}

int main(int ac, char **av, char **envp)
{
    (void) envp;
    t_env *p;

    if (ac == 1)
        return (printf("No philosophers\n"));
    p = malloc(sizeof(t_env));
    *p = (t_env){0};
    p->nb_philos = ft_atoi(av[1]);
    put_philo(p);
    printf("%d\n", p->t);
}