# **************************************************************************** #
#                                                                              #
#    libft                                                                     #
#                                                                              #
# **************************************************************************** #

NAME		= libft.a

CC			= gcc
CFLAGS		= -Wall -Wextra -Werror -g
RM			= rm -f

# ── Directories ──────────────────────────────────────────────────────────── #
OBJ_DIR		= obj

# ── Sources ──────────────────────────────────────────────────────────────── #
SRCS		= \
	file/ft_putstr_fd.c \
	file/ft_putendl_fd.c \
	file/ft_putnbr_fd.c \
	file/ft_putchar_fd.c \
	lst/ft_lstadd_back.c \
	lst/ft_lstadd_front.c \
	lst/ft_lstclear.c \
	lst/ft_lstdelone.c \
	lst/ft_lstiter.c \
	lst/ft_lstlast.c \
	lst/ft_lstmap.c \
	mem/ft_memset.c \
	mem/ft_bzero.c \
	mem/ft_calloc.c \
	mem/ft_memchr.c \
	mem/ft_memcmp.c \
	mem/ft_memcpy.c \
	mem/ft_memmove.c \
	nbr/ft_atoi.c \
	nbr/ft_itoa.c \
	others/ft_isprint.c \
	others/ft_isdigit.c \
	others/ft_isalnum.c \
	others/ft_isalpha.c \
	others/ft_isascii.c \
	str/ft_strjoin.c \
	str/ft_strdup.c \
	str/ft_tolower.c \
	str/ft_strtrim.c \
	str/ft_strlcat.c \
	str/ft_substr.c \
	str/ft_strlcpy.c \
	str/ft_strlen.c \
	str/ft_toupper.c \
	str/ft_strmapi.c \
	str/ft_split.c \
	str/ft_strncmp.c \
	str/ft_strchr.c \
	str/ft_strnstr.c \
	str/ft_strrchr.c \
	str/ft_striteri.c \
	str/ft_strcmp.c \
	get_next_line_bonus.c

OBJS		= $(SRCS:%.c=$(OBJ_DIR)/%.o)

# ── Colors ───────────────────────────────────────────────────────────────── #
GREEN		= \033[1;32m
YELLOW		= \033[1;33m
RED			= \033[1;31m
RESET		= \033[0m

# ── Rules ────────────────────────────────────────────────────────────────── #
all: $(NAME)

$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "$(YELLOW)  Compiling $<$(RESET)\n"

clean:
	@rm -rf $(OBJ_DIR)
	@printf "$(RED)✗ libft objects removed$(RESET)\n"

fclean: clean
	@$(RM) $(NAME)
	@printf "$(RED)✗ $(NAME) removed$(RESET)\n"

re: fclean all

.PHONY: all clean fclean re