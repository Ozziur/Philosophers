# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mruizzo <mruizzo@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/06 17:03:05 by mruizzo           #+#    #+#              #
#    Updated: 2022/07/07 18:53:25 by mruizzo          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC = check.c main.c time.c utils.c game.c philo_utility.c monitor.c


SRCS = $(addprefix src/, $(SRC))

OBJS = $(SRCS:.c=.o)

CC = gcc

FLAGS = -Wall -Werror -Wextra #-fsanitize=address -g3

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(SRCS) -pthread -o $(NAME)

all: $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re