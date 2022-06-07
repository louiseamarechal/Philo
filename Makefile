# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lmarecha <lmarecha@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/30 15:24:06 by lmarecha          #+#    #+#              #
#    Updated: 2022/06/07 08:55:23 by lmarecha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

# SRC = milliseconds.c
SRC = main.c

CC = clang
CFLAGS = -Wall -Werror -Wextra -pthread #-g3 -fsanitize=address
INCLUDES = -I includes

OBJ = $(SRC:.c=.o)

HEADER = includes/philosopher.h

all: $(NAME)

$(NAME): $(OBJ) $(HEADER)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(INCLUDES)

clean:
	/bin/rm -f *.o

fclean: clean
	/bin/rm -f $(NAME)

.c.o: $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o) $(INCLUDES)

re: fclean all

.PHONY: all clean fclean re
