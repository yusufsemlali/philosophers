CC = cc
FLAGS = -Wall -Wextra -Werror 
SRC = src/main.c src/utils.c 
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


