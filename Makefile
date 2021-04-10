# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kait-mar <kait-mar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/30 17:15:38 by molabhai          #+#    #+#              #
#    Updated: 2021/03/09 09:52:05 by molabhai         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= minishell

CC= gcc -g

FLAGS= -Wall -Wextra -Werror

SRCS=  cd.c cd_utility.c pwd.c export.c \
	   export_utility.c export_utility_two.c \
	   unset.c main.c echo/echo.c echo/echo_utility.c keep_split.c \
	   executables.c echo/echo_utility_two.c meta.c file_append.c \
	   exit.c redirect_output.c pipe_file.c redirect_input.c signals.c \
	   semi_colon.c dollar_sign.c escape_character.c minishell_utility.c \
	   dollar_sign_utility.c executable_utility.c echo/echo_utility3.c echo/echo_utility4.c \
	   echo/echo_utility5.c history.c echo/echo_utility6.c command_navigation.c main_helper.c \
	   meta_helper.c meta_support.c meta_support_two.c main_norm_helper.c history_support.c \

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
	$(CC)   $(SRCS)  -ltermcap Libft/libft.a Printf/libftprintf.a -o minishell

clean:
	$(DELETEOBJ) $(DELETENAME)
	cd Libft && make fclean -f Makefile
	cd Printf && make fclean -f Makefile

re: clean all