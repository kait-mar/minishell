/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molabhai <molabhai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 17:29:54 by molabhai          #+#    #+#             */
/*   Updated: 2020/12/09 18:24:34 by molabhai         ###   ########.fr       */
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

typedef struct s_export
{
	char 	*command;
	char	**argument;
	char	**env;
	int 	flag;
}				t_export;

void	cd_command(char *argument, int i);
char	**taking_command(char *str);
char 	**split_to_tokens(char *str);
char	*reading_input(char *str);
char	*without_that(char *str, char c);
int		how_mutch_argument(char *str, int i);
char	*ft_toStrLower(char *str);
void	pwd_command(void);
int		check_pwd(char *str);
int		check_env(char *str);
void	env_command(char **str, char **splits);
void	export_command(char **env, char *splits);
int		how_mutch_arguments(char **splits, int i);
int		check_exp_lex(char *str);
int		match(char *str, char  *export);
int		arguments_in(char **splits, int i);
void	free_export(t_export *export);
char	**take_only_carac(char *str);
int		check_quote(char *str);
int		check_double_quote(char *str);
void	free_splits(char **splits);
char	*front_append(char *string, char *to_append);
t_export	*check_export(char **splits, char **env);

#endif
