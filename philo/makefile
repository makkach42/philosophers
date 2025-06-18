NAME = philo
CC = cc
RM = rm -rf
FLAGS = -Wall -Werror -Wextra

SRC = philo.c tools.c tools_two.c tools_three.c routine_monitor.c free_all.c routine_philos.c
OBJ = $(SRC:.c=.o)

all:	$(NAME)

$(NAME):	$(OBJ)
	$(CC) $(FLAGS) $(OBJ) -pthread -o $(NAME)

%.o:	%.c philo.h
	$(CC) $(FLAGS) -c $< -o $@

clean: 
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all
