CC		=	gcc
TESTFLAG	=	-lreadline
CFLAG		=	-Wall -Wextra -Werror -lreadline


all 		:
			@$(CC) $(TESTFLAG) libft/libft.a src/*.c