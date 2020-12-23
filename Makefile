# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: molabhai <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/30 17:15:38 by molabhai          #+#    #+#              #
#    Updated: 2020/12/23 16:55:23 by molabhai         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



NAME= minishell

CC= gcc -g

FLAGS= -Wall -Wextra -Werror

SRCS=  cd.c cd_utility.c pwd.c export.c \
	   export_utility.c export_utility_two.c \
	   unset.c main.c echo.c echo_utility.c keep_split.c\
	   executables.c echo_utility_two.c meta.c

OBJ = $(SRCS:.c=.o)

HEADERS= minishell.h

DELETEOBJ= rm -rf *.o

DELETENAME= rm -rf $(NAME)

MAKINGLIBFT= cd Libft && make -f Makefile

MAKINGPRINTF= cd Printf && make -f Makefile


all: $(NAME)

$(NAME):
	$(MAKINGLIBFT)
	$(MAKINGPRINTF)
	$(CC)   $(SRCS)  Libft/libft.a Printf/libftprintf.a -o minishell 

clean:
	$(DELETEOBJ) $(DELETENAME)
	cd Libft && make fclean -f Makefile
	cd Printf && make fclean -f Makefile


re: clean all
