##
## Makefile for  in /home/joubert/delivery/PSU_2016_minishell2
## 
## Made by Joubert Miguel
## Login   <miguel.joubert@epitech.eu>
## 
## Started on  Wed Mar 15 13:04:12 2017 Joubert Miguel
## Last update Thu Mar 16 01:18:30 2017 Joubert Miguel
##

CC	=	gcc

FLAGS	=	-g -Wall -Werror -W -Wextra

PROJECT =	src/minishell1.c		\
		src/minishell2.c		\
		src/cd.c			\
		src/check_shell.c		\
		src/double_out.c		\
		src/double_in.c			\
		src/env.c			\
		src/in.c			\
		src/pipe.c			\
		src/out.c			\
		src/path.c			\
		src/retpath.c			\
		src/semicolon.c			\
		src/signal.c			\
		src/tools.c			\
		src/tools_bis.c			\
		src/verify_cd.c			\
		src/verify_env.c		\
		src/verify.c			\

NAME	=	mysh

all:	$(NAME)

$(NAME):	$(PROJECT)
	$(CC) $(FLAGS) $(PROJECT) -o $(NAME) -L. -lgnl

clean:
	rm -f $(NAME)

fclean:	clean

re:	fclean	all