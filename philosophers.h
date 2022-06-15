#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

typedef struct t_info
{
//	pthread_t		content;
//	pthread_mutex_t mutex;
	int	nb_philos;
	int time_to_die;
	int  time_to_eat;
	int    time_to_sleep;
	int number_of_times_each_philosopher_must_eat;
	int fork;
	int thread;
	int i;
	int t;
	struct t_info	*next;
}t_info;


typedef struct t_philo{
	int number;
	int nb_philos;
	int is_dead;
	pthread_t		content;
	pthread_mutex_t mutex;
	struct t_philo *next;
}t_philo;

t_philo	*create_liste(t_philo *p);
t_philo	*ft_addback(t_philo *p);
void    *routine();
int	ft_atoi(const char *str);
void ft_threadjoin(t_philo *p);
int is_dead(t_philo *p);
#endif