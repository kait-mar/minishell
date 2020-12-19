/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molabhai <molabhai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 17:29:54 by molabhai          #+#    #+#             */
/*   Updated: 2020/12/12 19:00:21 by molabhai         ###   ########.fr       */
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

typedef struct s_unset
{
	char	*argument;
	struct s_unset	*next;
}				t_unset;

typedef struct s_env
{
	char	*in_env;
	struct s_env	*next;
}				t_env;
typedef	struct s_spaces
{
	char	*bult;
	int		spaces;
}			t_spaces;

void	cd_command(char *argument, int i);
char	**taking_command(char *str);
char	**split_to_tokens(char *str);
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
int		check_unset(char *str);
void	unset_command(char **env, char *str);
t_env		*filling_env(char **env);
t_env		*adding_last(t_env *head, int i, char *env);
int			kait_count(char *str);
int			check_single_quotes(char c);
int			check_double_quotes(char c);
int			check_single_double_quote(char c);
void	ft_putstr(char *s);
int		print(char **bult, char **env);
int		find(char *str, char c);
void	quote_dquote(char *line);
int		echo(char *argv, char **env);
int		ft_strcmp(const char *s1, const char *s2);
char	**keep_split(char *s, char c, char b);
int		print_env(char *bult, char **env, int which_quote);
int		echo_strcmp(const char *s1, const char *s2);
void	put_cases(char **bult, char **env);
void	put_normal(char **split, char **env, int i);

#endif
