# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lmarecha <lmarecha@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/30 15:24:06 by lmarecha          #+#    #+#              #
#    Updated: 2022/06/24 12:22:22 by lmarecha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#------------------------------------#
#             COMPILATION            #
#------------------------------------#

NAME = philo

CC = clang
CFLAGS = -Wall -Werror -Wextra -pthread #-g3 -fsanitize=address
INCLUDES = -I includes

#------------------------------------#
#               SOURCES              #
#------------------------------------#

SRCDIR		=	src/

SRCMAIN		=	main.c

SRCEXECUTOR	=	executor.c

SRCPARSER	=	initializer.c

SRCUTILS	=	philo_utils.c \
				timestamp.c

SRC 		=	$(addprefix $(SRCDIR), $(SRCMAIN)) \
				$(addprefix $(SRCDIR)executor/, $(SRCEXECUTOR)) \
				$(addprefix $(SRCDIR)parser/, $(SRCPARSER)) \
				$(addprefix $(SRCDIR)utils/, $(SRCUTILS))

#------------------------------------#
#               OBJECTS              #
#------------------------------------#

OBJ = $(SRC:.c=.o)

#------------------------------------#
#               HEADER               #
#------------------------------------#

HEADER = includes/philosopher.h

#------------------------------------------------------------------------------#
#                                                                              #
#                                   RULES                                      #
#                                                                              #
#------------------------------------------------------------------------------#

all: $(NAME)

$(NAME): $(OBJ) $(HEADER)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(INCLUDES)

clean:
	/bin/rm -f $(OBJ)

fclean: clean
	/bin/rm -f $(NAME)

.c.o: $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o) $(INCLUDES)

re: fclean all

.PHONY: all clean fclean re
