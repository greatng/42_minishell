NAME			=	minishell

LEAKS			=	-fsanitize=address -fno-omit-frame-pointer
CC			=	gcc
CFLAGS			=	-Wall -Wextra -Wextra
READFLAG		=	-lreadline

HEADER_DIR		=	include
HEADER			=	minishell builtin
HEADERS			=	$(addprefix $(HEADER_DIR)/, $(addsuffix .h, $(HEADER)))

SRC_DIR			=	src
SRC			=	main builtin_1 additional_fn signal 1_phrase_utils 2_lexer 3_parser 4_free_phrase \
					rl_get convert builtin_2
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

all:				$(NAME)

$(NAME):			$(OBJ) libft
					@echo "$(GREEN)Compiling:$(NORMAL)"
					$(CC) $(CFLAGS) $(READFLAG) $(LEAKS) $(OBJ) $(LIBFT) -o $@

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c	$(HEADERS)
					@mkdir -p $(OBJ_DIR)
					@$(CC) $(CFLAGS) -c $< -o $@ 

libft:
					@make -C ./libft/		
					

clean:
					@$(RM) -rf $(OBJ) $(OBJ_B) $(OBJ_DIR)
					@make clean -C ./libft/	
fclean:				clean
					@$(RM) -rf $(NAME)
					@make fclean -C ./libft/	
					
re:					fclean all

.PHONY:				all clean fclean re libft

pig:				
					@echo "$(SALMON)                         .....            :!????7!^:\n\
                   .^!J5PGGBGG5::~!77?77~:G&&&&&&&&#GY!.\n\
                 .?G#&&&&&&&&&B^G&&&&&&&B^G&&&&&&&&&&&#^\n\
                 .P&&&&&&&&&&#!?&&&&&&&&&J~B&&&&&&&&#Y^\n\
                  .JB&&&&&&&G!J&&&&&&&&&&&Y!YB###B5J??^\n\
                   ~??5GGG5?7P&&&&&&&&&&&&&#5JJJJJ5G&&#5^\n\
                 .J&&BPYYY5G&&&&&&&&&&&&&&&&&&&#&&&&&&&&#~\n\
                .Y&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&B^\n\
                !&&&&&&&&&&&&BG#&&&&&&&&&BJY#&&&&&&&&&&&&&P.\n\
               .5&&&&&&&&&&&#^ ?&&&&&&&&&5:^B&&&&&&&&&&&&&&Y.\n\
               ^#&&&&&&&&&&&&BPB$(HOTPINK)#BGGGGGGGBB$(SALMON)#&&&&&&&&&&&&&&&&J.\n\
              .5&&&&&&&&&&&&&$(HOTPINK)#BPPPP5PP55PPPPB$(SALMON)&&&&&&&&&&&&&&&&!\n\
              7&&&&&&&&&&&&&&$(HOTPINK)#PPPP?^5P!~PPPPG&$(SALMON)&&&#######&&&&&5.\n\
             .Y&&&&&#######&&&$(HOTPINK)BGPP55PPP5PPGB#$(SALMON)&&&#BBGBGBB##&&&B:\n\
              J&&&##BBBBBB##&&&&$(HOTPINK)#BBBBBB#PB$(SALMON)&&&&&##BGGPPGBB#&&&P.\n\
              :B&&#BBGPPGGB##&&&&#JYPPPJ?B&&&&&&#BBGGGBB##&&#!\n\
               ^G&&#BBGGGBB#&&&&&&#BPPGB&&&&&&&&########BBP!.\n\
                .?G########&&&&&&&&&&&&&&&&&&&&&&&&#G5YJJJYY5PY!.\n\
                   ^7J5GB#&&&&&&&&&&&&&&&&&&&&&&&&#YJPG##&&&&&@P.\n\
               :~!!777777?B&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&#GJ:\n\
             .J#&&&&&&&&&#&&&&&&&&&&&&&&&&&&&&&&&&&&&#BBP5?!^.\n\
             .7B#&&&&&&&&#&&&&&&&&&&&&&&&&&&&&&&&&&&&Y^.\n\
               .^~!777777Y#&&&&&&&&&&&&&&&&&&&&&&&&&&&?\n\
                        ~&&&&&&&&&&&&&&&&&&&&&&&&&&&&&P.\n\
                        ^#&&&&&&&&&&&&&&&&&&&&&&&&&&&&G.\n\
                         ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~^\n\
				      $(NORMAL)I'm the piglosopher !"