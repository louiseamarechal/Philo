# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lmarecha <lmarecha@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/30 15:24:06 by lmarecha          #+#    #+#              #
#    Updated: 2022/05/30 17:42:53 by lmarecha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC = milliseconds.c
# SRC = main.c

CC = clang

CFLAGS = -Wall -Werror -Wextra -pthread #-g3 -fsanitize=address

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

clean:
	/bin/rm -f *.o

fclean: clean
	/bin/rm -f $(NAME)

.c.o: #$(addprefix , push_swap.h)
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

re: fclean all

.PHONY: all clean fclean re
