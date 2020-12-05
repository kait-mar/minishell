/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molabhai <molabhai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 17:29:54 by molabhai          #+#    #+#             */
/*   Updated: 2020/12/05 12:03:03 by molabhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
 #define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <dirent.h>
#include "./Libft/libft.h"

typedef struct s_command_cd
{
	char *command;
	char *argument;
	int wich_path;
	int error;
}				t_command_cd;


char	*cd_command(char *argument, int i);
char	**taking_command(char *str);
char 	**split_to_tokens(char *str);
char	*reading_input(char *str);
char	*without_that(char *str, char c);
int		how_mutch_argument(char *str, int i);

#endif
