/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebackor <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 16:39:31 by lebackor          #+#    #+#             */
/*   Updated: 2022/08/01 21:23:15 by lebackor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct t_info
{
	long long			current_time;
	pthread_mutex_t		print;
	pthread_mutex_t		meal;
	pthread_mutex_t		canprint;
	pthread_mutex_t		candeath;
	int					nb_philos;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					number_of_times_each_philosopher_must_eat;
	int					fork;
	int					thread;
	int					i;
	int					t;
	int					can_print;
	int					someoneisdead;
	struct t_info		*next;
}t_info;

typedef struct t_philo{
	int				number;
	int				is_dead;
	int				meal;
	long long		time;
	long long		time_of_last_meal;
	pthread_t		content;
	pthread_mutex_t	mutex;
	struct t_info	*tg;
	struct t_philo	*next;
}t_philo;

t_philo		*create_liste(t_philo *p);
t_philo		*ft_addback(t_philo *p, t_info *philo, int i);
int			ft_atoi(const char *str);
void		ft_threadjoin(t_philo *p);
int			is_meal(t_philo *p);
void		ft_thread(t_philo *p);
void		print(long long time, t_philo *p, char *str);
void		mutex_destroy(t_philo *p);
void		ft_clean(t_philo *p, t_info *philo);
void		ft_death(t_philo *p);
int			init_philo(t_info *philos, int ac, char **av);
void		increase_meal(t_philo *philo);
void		*routine(void *pol);
void		*one_philo(t_philo *philo);
void		*routine1(void *pol);
long long	get_time(void);
int			is_dead(t_philo *philo);
//int	check_time(t_philo *p);
#endif
