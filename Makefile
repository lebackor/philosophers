SRCS = 		philosophers.c\
			philosophers2.c\
			liste.c\
			utils.c\
			checking.c\
			utils2.c\
			

OBJS = ${SRCS:.c=.o}

CC	=	gcc

CFLAGS = -Wall -Werror -Wextra -g3 #-fsanitize=thread

NAME = philo

all : ${NAME}

${NAME} :	${OBJS}
	@$(CC) -pthread $(CFLAGS) $(OBJS) -o $@
	@echo "Ca arrive..."


%.o: %.c
	@${CC} ${CFLAGS} -I includes -c $< -o ${<:.c=.o} 
 

clean :
		rm -f ${OBJS}

fclean :	clean
			rm -f ${NAME}

re : fclean all

.PHONY: all clean fclean re
