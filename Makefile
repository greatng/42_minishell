CC		=	gcc
CFLAG		=	-Wall -Wextra -Werror -lreadline


all 		:
			@$(CC) $(CFLAG) libft/libft.a src/*.c