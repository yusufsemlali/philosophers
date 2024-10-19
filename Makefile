CC = cc
FLAGS = -Wall -Wextra -Werror -ggdb -fsanitize=thread 
SRC = src/main.c src/utils.c src/init.c src/threads.c src/observe.c src/cycle.c src/extra_utils.c\
			#    ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
			#    ft_lstclear.c ft_lstadd_back.c ft_lstdelone.c ft_del.c ft_dellast.c \
			# ft_putendl_fd.c\

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


