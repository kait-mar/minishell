# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: molabhai <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/30 17:15:38 by molabhai          #+#    #+#              #
#    Updated: 2020/12/01 18:21:18 by molabhai         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



NAME= minishell

CC= gcc

FLAGS= -Wall -Wextra -Werror

SRCS= cd.c main.c

OBJ = $(SRCS:.c=.o)

HEADERS= minishell.h

DELETEOBJ= rm -rf *.o

DELETENAME= rm -rf $(NAME)

MAKING= cd Libft && make -f Makefile


all: $(NAME)

$(NAME):
	$(MAKING)
	$(CC) $(FLAGS)  $(SRCS)  Libft/libft.a -o minishell

clean:
	$(DELETEOBJ) $(DELETENAME)


re: clean all
