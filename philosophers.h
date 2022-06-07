#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
#include <stdio.h>
#include <pthread.h>

typedef struct t_env
{
	pthread_t		*content;
	struct t_env	*next;
}t_env;


#endif