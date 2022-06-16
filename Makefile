NAME			=	minishell
UNAME 			= 	$(shell uname -s)
ARCH 			= 	$(shell arch)

CC			=	gcc
CFLAGS			=	-Wall -Wextra -Wextra
LEAKS			=	-fsanitize=address
READFLAG		=	-lreadline

ifeq ($(UNAME), Darwin)
	ifeq ($(ARCH), arm64)
		LDFLAGS			=	-L${HOMEBREW_PREFIX}/opt/readline/lib
		CPPFLAGS		=	-I${HOMEBREW_PREFIX}/opt/readline/include
	else ifeq ($(ARCH), i386)
		LDFLAGS			=	-L/usr/local/opt/readline/lib
		CPPFLAGS		=	-I/usr/local/opt/readline/include
	endif
endif

HEADER_DIR		=	include
HEADER			=	minishell builtin phrase quote
HEADERS			=	$(addprefix $(HEADER_DIR)/, $(addsuffix .h, $(HEADER)))

SRC_DIR			=	src
SRC			=	main ms_builtin_1 ms_builtin_2 ms_builtin_utils ms_free_heredoc \
					ms_end ms_free_phrase ms_lexer ms_parser ms_pipe ms_heredoc \
					ms_check_phrases ms_quote_utils ms_rl_get ms_signal ms_translate_vars \
					ms_init ms_conver_1 ms_conver_2 ms_path ms_run_builtin ms_collect \
          ms_check_phrases_2 ms_quote_utils_2
SRCS 			=	$(addprefix $(SRC_DIR)/, $(addsuffix .c, $(SRC)))

OBJ_DIR			=	obj
OBJ			=	$(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(SRC)))

LIBFT			=	libft/libft.a

GREEN = \033[38;5;2m
NORMAL = \033[38;5;255m
RED = \033[38;5;1m
BLUE = \033[38;5;4m
SALMON = \033[38;5;174m
HOTPINK = \033[38;5;168m

all:				libft $(NAME)

$(NAME):			$(OBJ)
					@echo "$(GREEN)Compiling:$(NORMAL)"
					$(CC) $(CFLAGS) $(LEAKS) $(READFLAG) $(LDFLAGS) $(CPPFLAGS) $(OBJ) $(LIBFT) -o $@

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c $(HEADERS) 
					@mkdir -p $(OBJ_DIR)
					@$(CC) $(CPPFLAGS) $(CFLAGS)  -c $< -o $@ 

libft:
					@make -C ./libft/	
					

clean:
					@$(RM) -rf $(OBJ) $(OBJ_B) $(OBJ_DIR)
					@make clean -C ./libft/	
fclean:				clean
					@$(RM) -rf $(NAME)
					@make fclean -C ./libft/	
					
re:					fclean all

.PHONY:				all clean fclean re libft leaks

leaks:				libft $(OBJ)
					@echo "$(GREEN)Compiling:$(NORMAL)"
					$(CC) $(CFLAGS) $(LEAKS) $(READFLAG) $(LDFLAGS) $(CPPFLAGS) $(OBJ) $(LIBFT) -o $@
