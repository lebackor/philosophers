#include "philosophers.h"

void    *routine(void * xx)
{
    printf("4xd\n");
}

int main(int ac, char **av, char **envp)
{
    (void) envp;
    t_env p;

    pthread_create(&p.content, NULL, routine, NULL);
    pthread_join(&p.content, NULL);
}