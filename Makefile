# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kait-mar <kait-mar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/30 17:15:38 by molabhai          #+#    #+#              #
#    Updated: 2021/06/07 12:41:13 by molabhai         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
NAME= minishell

CC= gcc

FLAGS= -Wall -Wextra -Werror

SRCS=  cd/cd.c cd/cd_utility.c pwd/pwd.c export/export.c \
	   export/export_utility.c export/export_utility_two.c \
	   unset/unset.c unset/unset_helper.c unset/unset_helper2.c  echo/echo.c echo/echo_utility.c \
	   minishell_utils/keep_split.c minishell_utils/keep_split_helper.c  minishell_utils/keep_split_helper2.c \
	   executable/executables.c echo/echo_utility_two.c  redirection/file_append.c \
	   exit/exit.c redirection/redirect_output.c pipe/pipe_file.c redirection/redirect_input.c signals.c \
	   dollar_sign/dollar_sign.c escape_character/escape_character.c escape_character/escape_character_helper.c \
	    escape_character/escape_character_helper2.c  escape_character/escape_character_helper3.c \
	   escape_character/escape_character_helper4.c escape_character/escape_character_helper5.c \
	   dollar_sign/dollar_sign_utility.c echo/echo_utility3.c echo/echo_utility4.c \
	   executable/executable_utility.c  \
	   echo/echo_utility5.c bash_history/history.c echo/echo_utility6.c bash_history/command_navigation.c \
	      bash_history/history_support.c \
	   dollar_sign/dollar_sign3.c cd/cd_utility3.c cd/cd_utility4.c  cd/cd_utility5.c \
	   echo/echo_support.c echo/echo_utility_helper.c bash_history/command_navigation_norme.c export/export_support.c \
	   export/export_support_two.c export/export_utility_three.c export/export_utility_support.c export/export_utility_support_two.c \
	   export/export_utility_support_three.c export/export_utility_support_four.c export/export_utility_support_five.c \
	 	dollar_sign/dollar_sign_utility_two.c \
	   redirection/redirect_output_helper.c export/export_utility_two_support.c  export/export_utility_two_support2.c \
	   export/export_utility_support3.c export/export_utility_support4.c export/export_utility_support5.c \
	   executable/executables_support.c executable/executable_support2.c executable/executable_support3.c \
	   executable/executable_support4.c executable/executable_support5.c executable/executable_support6.c \
	   exit/exit_support.c pipe/pipe_file_support.c redirection/redirect_output_helper2.c pwd/pwd_support.c \
	   export/export_free.c  \
	   dollar_sign/dollar_sign_support.c dollar_sign/dollar_sign_support2.c dollar_sign/realloc_input.c \
	   dollar_sign/dollar_sign_support3.c \
		echo/echo_conditions.c cd/cd_norme.c \
		export/export_v3.c  bash_history/command_support.c minishell_utils/minishell_utility2.c \
		minishell_utils/minishell_utility.c \
		main_meta/main_helper.c main_meta/main_helper_free.c main_meta/main_norm_helper.c \
		main_meta/main.c main_meta/meta.c main_meta/meta_support_two.c main_meta/meta_helper.c \
		main_meta/meta_support.c main_meta/meta2.c main_meta/meta_support2.c redirection/redirections_core.c \
		redirection/red_lines.c unset/unset_helper3.c redirection/redirection.c

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
	$(CC) $(FLAGS) $(SRCS) -ltermcap Libft/libft.a Printf/libftprintf.a -o minishell
clean:
	$(DELETEOBJ) $(DELETENAME)
	cd Libft && make fclean -f Makefile
	cd Printf && make fclean -f Makefile

fclean : clean
	rm -rf $(NAME)

re: clean all
