#include "philosophers.h"
void print(t_info *info, t_philo *p, char *str)
{
    (void)p;
    pthread_mutex_lock(&info->print);
    printf("%s", str);
    pthread_mutex_unlock(&info->print);

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