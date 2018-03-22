# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tgascoin <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/03 14:42:12 by tgascoin          #+#    #+#              #
#    Updated: 2017/02/21 10:43:56 by tgascoin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
NAME = ft_ls
FLAGS = -Wall -Wextra -Werror
SRC = Srcs/ft_args.c Srcs/ft_extras_1.c Srcs/ft_extras_2.c Srcs/ft_putnbr.c Srcs/ft_strapp.c Srcs/ft_strcmp.c Srcs/ft_strdel.c Srcs/ft_strdup.c Srcs/ft_strlen.c Srcs/ft_strnew.c Srcs/main.c Srcs/print_1.c Srcs/print_2.c
OBJ = ft_args.o ft_extras_1.o ft_extras_2.o ft_putnbr.o ft_strapp.o ft_strcmp.o ft_strdel.o ft_strdup.o ft_strlen.o ft_strnew.o main.o print_1.o print_2.o

all: $(NAME)

$(NAME):
	$(CC) $(FLAGS) -c $(SRC) -I Includes
	$(CC) $(OBJ) -o $(NAME)

clean:
	/bin/rm -f $(OBJ)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all
