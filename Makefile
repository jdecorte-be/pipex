NAME = pipex

CC = gcc

CFLAGS = -Werror -Wall -Wextra

RM = rm -rf

SRCS = 	pipex.c\
		main.c\
		libft/libft.a\

SRCS_BONUS = 	pipex_bonus.c\
				libft/libft.a\

$(NAME) :
	make all -C libft
	gcc -fsanitize=address $(CFLAGS) $(SRCS) -o $(NAME)

bonus :
	make all -C libft
	gcc -fsanitize=address $(CFLAGS) $(SRCS_BONUS) -o $(NAME)

all : $(NAME)

fclean : clean
	$(RM) $(NAME)
	make fclean -C libft

clean :
	$(RM) $(NAME)
	make clean -C libft

re : fclean all