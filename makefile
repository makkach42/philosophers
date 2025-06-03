NAME = philo
CC = cc
RM = rm -rf
FLAGS = -Wall -Werror -Wextra #-g3 -fsanitize=thread

SRC = philo.c tools.c tools_two.c routine_monitor.c free_all.c routine_philos.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) -pthread $(OBJ) -o $(NAME)

%.c: %.o philosophers.h
	$(CC) $(FLAGS) -c $< -o $@

clean: 
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all
