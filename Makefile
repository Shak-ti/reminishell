NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

# Libft
LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

# Srcs
SRC_DIR = src
SRCS = main.c \
	builtins/cd.c builtins/echo.c builtins/env.c builtins/export.c builtins/pwd.c builtins/unset.c builtins/exit.c \
	builtins/export_print.c \
	exec/exec.c exec/builtins.c exec/heredoc.c exec/get.c exec/heredoc2.c exec/clean.c exec/pipe.c exec/utils.c \
	exec/pipe_utils.c exec/pipe_utils2.c exec/pipe2.c exec/redir.c exec/close_pipes.c exec/child.c exec/redir2.c \
	parsing/parse.c parsing/create_cmd.c parsing/redir.c parsing/utils.c \
	token/free_tokens.c token/handlers.c token/print_tokens.c token/token_lst.c token/tokenize.c token/tokenize_utils.c \
	token/handle_operator.c \
	utils/free_tab.c utils/exit.c utils/ft_realloc.c utils/ft_strcmp.c utils/error.c \
	signals/signals.c \
	expand/expand.c expand/expand_utils.c expand/expand_handlers.c expand/expand_single_quote.c\
	env/envlst_create.c env/envlst_len.c env/envlst_remove.c env/envlst_update.c env/envlst_view.c env/env_init.c env/env_utils.c \
	syntax/syntax_functions.c syntax/syntax_utils.c syntax/syntax.c syntax/syntax_env.c
SRCS := $(addprefix $(SRC_DIR)/, $(SRCS))
OBJ_DIR = obj/
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))
INCLUDES = -I./include
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s --trace-children=yes --track-fds=yes $(V_FLAG)
V_FLAG = --suppressions="ignore_valgrind"

UNAME_S := $(shell uname -s)
# Readline
ifeq ($(UNAME_S),Linux)
	LDFLAGS =
	CPPFLAGS =
	LIBS = -lreadline -lncurses
else ifeq ($(UNAME_S),Darwin)
	READLINE_DIR := $(shell brew --prefix readline)
	LDFLAGS = -L$(READLINE_DIR)/lib
	CPPFLAGS = -I$(READLINE_DIR)/include
	LIBS = -lreadline
endif

# Colors
GREEN = \033[0;32m
RESET = \033[0m

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(OBJS) $(LIBFT) $(LDFLAGS) $(LIBS) -o $(NAME) -g
	@echo "$(GREEN)✅ $(NAME) has been created$(RESET)"

# Objects
$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(CPPFLAGS) $(INCLUDES) -c $< -o $@ -g

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)

# Build libft
$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

valgrind: $(NAME)
	$(VALGRIND) ./$(NAME)

clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@echo "$(GREEN)🧹 Object files cleaned$(RESET)"

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@echo "$(GREEN)🧹 $(NAME) cleaned$(RESET)"

re: fclean all

.PHONY: all clean fclean re valgrind
