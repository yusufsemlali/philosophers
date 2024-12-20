CC = cc
FLAGS = -Wall -Wextra -Werror -ggdb -fsanitize=thread
SRC = main.c utils.c init.c threads.c observe.c cycle.c extra_utils.c
OBJ = $(SRC:.c=.o)
NAME = philo


all: $(OBJ)
	@$(CC) $(FLAGS) $(SRC) -o $(NAME)
%.o : %.c
	@$(CC) $(FLAGS) -c $< -o $@
clean:
	@rm -rf $(OBJ)
fclean:
	@rm -f $(OBJ) $(NAME)
re: fclean all
.PHONY: all clean fclean re


