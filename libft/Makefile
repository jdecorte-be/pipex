NAME = libft.a

SRCS = \
	file/ft_putstr_fd.c \
	file/ft_putendl_fd.c\
	file/ft_putnbr_fd.c \
	file/ft_putchar_fd.c \
	\
	lst/ft_lstadd_back.c \
	lst/ft_lstadd_front.c\
	lst/ft_lstclear.c\
	lst/ft_lstdelone.c\
	lst/ft_lstiter.c\
	lst/ft_lstlast.c\
	lst/ft_lstmap.c\
	\
	mem/ft_memset.c \
	mem/ft_bzero.c \
	mem/ft_calloc.c \
	mem/ft_memchr.c \
	mem/ft_memcmp.c \
	mem/ft_memcpy.c \
	mem/ft_memmove.c \
	\
	nbr/ft_atoi.c \
	nbr/ft_itoa.c \
	\
	others/ft_isprint.c\
	others/ft_isdigit.c \
	others/ft_isalnum.c\
	others/ft_isalpha.c \
	others/ft_isascii.c\
	\
	str/ft_strjoin.c \
	str/ft_strdup.c\
	str/ft_tolower.c \
	str/ft_strtrim.c \
	str/ft_strlcat.c \
	str/ft_substr.c \
	str/ft_strlcpy.c \
	str/ft_strlen.c\
	str/ft_toupper.c \
	str/ft_strmapi.c \
	str/ft_split.c \
	str/ft_strncmp.c \
	str/ft_strchr.c\
	str/ft_strnstr.c \
	str/ft_strrchr.c \
	str/ft_striteri.c \

OBJS = ${SRCS:.c=.o}

OBJSBONUS = ${BONUS:.c=.o}

CC		= gcc
RM		= rm -f

CFLAGS = -Wall -Wextra -Werror

.c.o:
		${CC} ${CFLAGS} -g -c $< -o ${<:.c=.o}

$(NAME): ${OBJS}
		ar rcs ${NAME} ${OBJS}

all:	${NAME}

clean:
		${RM} ${OBJS} ${OBJSBONUS}

fclean:	clean
		${RM} ${NAME}

re:		fclean all