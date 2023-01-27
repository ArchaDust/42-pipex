# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aberneli <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/16 14:59:12 by aberneli          #+#    #+#              #
#    Updated: 2021/12/14 10:23:05 by aberneli         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME := pipex

CC := gcc
FLAGS := -Wall -Wextra -Werror -I.

HEADER := pipex.h get_next_line.h

SRC := main.c ft_pathjoin.c ft_splclean.c ft_split.c ft_strlen.c \
	resolve_exec.c exec_helper.c pipeline.c err.c get_next_line.c \
	get_next_line_utils.c heredoc_helper.c
OBJ := $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) -o $(NAME) $(OBJ)

%.o: %.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

rebonus: fclean

.PHONY: all clean fclean re
