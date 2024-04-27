CC = cc

FLAGS = -Wall -Wextra -Werror

NAME = philo

SRCS = main.c routine.c utils.c utils2.c

OBJS = $(SRCS:.c=.o)

$(NAME) : $(OBJS)
			$(CC) $(FLAGS) $(OBJS) -o $(NAME)

all : $(NAME)

clean :
			rm -f $(OBJS)

fclean : clean
			rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re