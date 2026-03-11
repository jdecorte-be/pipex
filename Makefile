# **************************************************************************** #
#                                                                              #
#    pipex                                                                     #
#                                                                              #
# **************************************************************************** #

NAME		= pipex

CC			= gcc
CFLAGS		= -Wall -Wextra -Werror -fsanitize=address
RM			= rm -rf

# ── Directories ──────────────────────────────────────────────────────────── #
OBJ_DIR		= obj
LIBFT_DIR	= libft
LIBFT		= $(LIBFT_DIR)/libft.a

# ── Sources ──────────────────────────────────────────────────────────────── #
SRCS		= src/pipex.c \
			  src/utils.c

SRCS_BONUS	= src_bonus/pipex_bonus.c \
			  src_bonus/utils_bonus.c

OBJS		= $(SRCS:%.c=$(OBJ_DIR)/%.o)
OBJS_BONUS	= $(SRCS_BONUS:%.c=$(OBJ_DIR)/%.o)

# ── Colors ───────────────────────────────────────────────────────────────── #
GREEN		= \033[1;32m
CYAN		= \033[1;36m
YELLOW		= \033[1;33m
RED			= \033[1;31m
RESET		= \033[0m

# ── Rules ────────────────────────────────────────────────────────────────── #
all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)
	@printf "$(GREEN)✔ $(NAME) compiled successfully$(RESET)\n"

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory
	@printf "$(CYAN)✔ libft compiled$(RESET)\n"

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "$(YELLOW)  Compiling $<$(RESET)\n"

bonus: fclean $(LIBFT) $(OBJS_BONUS)
	@$(CC) $(CFLAGS) $(OBJS_BONUS) $(LIBFT) -o $(NAME)
	@printf "$(GREEN)✔ $(NAME) (bonus) compiled successfully$(RESET)\n"

clean:
	@$(RM) $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean --no-print-directory
	@printf "$(RED)✗ Object files removed$(RESET)\n"

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean --no-print-directory
	@printf "$(RED)✗ $(NAME) removed$(RESET)\n"

re: fclean all

.PHONY: all clean fclean re bonus