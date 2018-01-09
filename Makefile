# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ddevico <ddevico@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/03 15:01:09 by ddevico           #+#    #+#              #
#    Updated: 2018/01/09 09:39:59 by davydevico       ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Matt_daemon
NAME_CLIENT = Ben_AFK

INCDIR = includes

FLAG = -Wall -Wextra -Werror

SRCDIR = src/
SRCCLI = src_client/

OBJ = 	$(SRC:.c=.o)
OBJ_C = 	$(SRC_CLIENT:.c=.o)

SRC =   $(SRCDIR)main.cpp \
		$(SRCDIR)Tintin_reporter.cpp \
		$(SRCDIR)Signal_handler.cpp

SRC_CLIENT = $(SRCCLI)main.cpp \

all: $(NAME) $(NAME_CLIENT)

$(NAME_CLIENT): $(OBJ_C)
	g++ -o $(NAME_CLIENT) $(OBJ_C) -I $(INCDIR) $(FLAG)

$(NAME): $(OBJ)
	g++ -o $(NAME) $(OBJ) -I $(INCDIR) $(FLAG)

%.o: %.c
	@g++ -o $@ -c $< $(FLAG)

clean:
	@rm -f $(OBJ)

fclean:
	@rm -f $(NAME) $(NAME_CLIENT)

re: fclean all

.PHONY: re fclean clean all
