#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

typedef struct t_env
{
	pthread_t		content;
	pthread_mutex_t mutex;
	int	nb_philos;
	int time_to_die;
	int  time_to_eat;
	int    time_to_sleep;
	int fork;
	int fork_used;
	int thread;
	int i;
	int t;
	struct t_env	*next;
}t_env;
t_env	*create_liste(t_env *p);
t_env	*ft_addback(t_env *p);
void    *routine();
int	ft_atoi(const char *str);
void ft_threadjoin(t_env *p);

#endif