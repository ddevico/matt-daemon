# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ddevico <ddevico@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/03 15:01:09 by ddevico           #+#    #+#              #
#    Updated: 2018/01/08 11:18:57 by ddevico          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Matt_daemon

INCDIR = includes

FLAG = -Wall -Wextra -Werror

SRCDIR = src/

OBJ = 	$(SRC:.c=.o)

SRC =   $(SRCDIR)main.cpp \

all: $(NAME)

$(NAME): $(OBJ)
	g++ -o $(NAME) $(OBJ) -I $(INCDIR) $(FLAG)

%.o: %.c
	@g++ -o $@ -c $< $(FLAG)

clean:
	@rm -f $(OBJ)

fclean:
	@rm -f $(NAME)

re: fclean all

.PHONY: re fclean clean all
