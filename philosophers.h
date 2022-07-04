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
	pthread_mutex_t print;
	int	nb_philos;
	int time_to_die;
	int  time_to_eat;
	int    time_to_sleep;
	long long current_time;
	
	int number_of_times_each_philosopher_must_eat;
	int fork;
	int thread;
	int i;
	int t;
	int can_print;
	struct t_info	*next;
}t_info;


typedef struct t_philo{
	int number;
	int is_dead;
	int  time_to_eat;
	int meal;
	long long time;
	long long current_time;
	long long time_of_last_meal;
	pthread_t		content;
	pthread_mutex_t mutex;
	struct t_info *tg;
	struct t_philo *next;
}t_philo;

t_philo	*create_liste(t_philo *p);
t_philo	*ft_addback(t_philo *p, t_info *philo, int i);
void    *routine();
int	ft_atoi(const char *str);
void ft_threadjoin(t_philo *p);
int is_dead(t_philo *p);
int is_meal(t_philo *p);
long long get_time(void);
void ft_thread(t_philo *p);
void print(long long time, t_philo *p, char *str);
void mutex_destroy(t_philo *p);
void ft_clean(t_philo *p, t_info *philo);
void	ft_usleep(long long time);
void    ft_death(t_philo *p);
#endif