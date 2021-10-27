NAME = pipex

CC = gcc

CFLAGS = -Werror -Wall -Wextra

RM = rm -rf

SRCS = 	pipex.c\
		libft/str/ft_split.c\
		libft/str/ft_strjoin.c\
		libft/str/ft_strlen.c\
		libft/mem/ft_calloc.c\
		libft/mem/ft_bzero.c\
		libft/str/ft_strlcpy.c\
		libft/str/ft_substr.c

$(NAME) :
	make all -C libft
	#gcc $(SRCS) -o $(NAME) -fsanitize=address
	gcc $(CFLAGS) $(SRCS) -o $(NAME)

all : $(NAME)

fclean : clean
	$(RM) $(NAME)
	make fclean -C libft

clean :
	$(RM) $(NAME)
	make clean -C libft

re : fclean all