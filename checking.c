#include "philosophers.h"

int is_dead(t_philo *p)
{
    t_philo *tmp;
    int i;
 //   (void)i;
//    (void) tmp;
    i = 0;
    tmp = p;
    while (i < p->tg->nb_philos)
    {
        if (tmp->is_dead == 1)
            return (1);
        //tmp = tmp->next;
        i++;
    }
    return (0);
}