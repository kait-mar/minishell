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

SRCS=  cd/cd.c cd/cd_utility.c pwd.c export/export.c \
	   export/export_utility.c export/export_utility_two.c \
	   unset.c main.c echo/echo.c echo/echo_utility.c keep_split.c \
	   executable/executables.c echo/echo_utility_two.c meta.c file_append.c \
	   exit.c redirect_output.c pipe_file.c redirect_input.c signals.c \
	   semi_colon.c dollar_sign/dollar_sign.c escape_character.c minishell_utility.c \
	   dollar_sign/dollar_sign_utility.c executable/executable_utility.c echo/echo_utility3.c echo/echo_utility4.c \
	   echo/echo_utility5.c bash_history/history.c echo/echo_utility6.c bash_history/command_navigation.c \
	   main_helper.c meta_helper.c meta_support.c meta_support_two.c main_norm_helper.c bash_history/history_support.c \
	   dollar_sign/dollar_sign3.c cd/cd_utility3.c cd/cd_utility4.c \
	   echo/echo_support.c echo/echo_utility_helper.c bash_history/command_navigation_norme.c export/export_support.c \
	   export/export_support_two.c export/export_utility_three.c export/export_utility_support.c export/export_utility_support_two.c \
	   export/export_utility_support_three.c export/export_utility_support_four.c export/export_utility_support_five.c \
	 	dollar_sign/dollar_sign_utility_two.c \
	   redirect_output_helper.c export/export_utility_two_support.c  export/export_utility_two_support2.c \
	   export/export_utility_support3.c export/export_utility_support4.c export/export_utility_support5.c \
	   executable/executables_support.c executable/executable_support2.c executable/executable_support3.c \
	   executable/executable_support4.c executable/executable_support5.c executable/executable_support6.c

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