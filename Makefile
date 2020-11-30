# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: molabhai <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/30 17:15:38 by molabhai          #+#    #+#              #
#    Updated: 2020/11/30 18:02:56 by molabhai         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



NAME= minishell

CC= gcc

FLAGS= -Wall -Wextra -Werror

SRCS= cd.c

OBJ = $(SRCS:.c=.o)

HEADERS= minishell.h

DELETEOBJ= rm -rf *.o


MAKING= cd Libft && make -f Makefile

all: $(NAME)

$(NAME):
	$(MAKING)
	$(CC) $(FLAGS)  $(SRCS)  Libft/libft.a -o minishell

clean:
	$(DELETEOBJ)
