/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molabhai <molabhai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 17:29:54 by molabhai          #+#    #+#             */
/*   Updated: 2020/12/26 11:04:09 by molabhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
 #define MINISHELL_H
 #define TRUE 1
 #define FALSE 0

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

/*	Metacharacter "Semicolon" */


typedef struct s_meta
{
	char	*argument;
	int		command;
	char	meta;
	struct	s_meta	*next;
}				t_meta;

void	cd_command(char *argument, int *status);
char	**taking_command(char *str);
char	**split_to_tokens(char *str);
char	*reading_input(void);
char	*without_that(char *str, char c);
int		how_mutch_argument(char *str, int i);
char	*ft_toStrLower(char *str);
void	pwd_command(int *status);
int		check_pwd(char *str);
int		check_env(char *str);
void	env_command(char **str, t_meta *meta, int *status);
void	export_command(char **env, char *splits, int *status);
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
void	unset_command(char **env, char *str, int *status);
t_env		*filling_env(char **env);
t_env		*adding_last(t_env *head, int i, char *env);
int			kait_count(char *str);
int			check_single_quotes(char c);
int			check_double_quotes(char c);
int			check_single_double_quote(char c);
void	ft_putstr(char *s);
int		print(char **bult, char **env, int *status);
int		find(char *str, char c);
void	quote_dquote(char *line);
int		echo(char *argv, char **env, int *status);
int		ft_strcmp(const char *s1, const char *s2);
char	**keep_split(char *s, char c, char b);
int		print_env(char *bult, char **env, int which_quote, int *status);
int		echo_strcmp(const char *s1, const char *s2);
void	put_cases(char **bult, char **env, int *status);
void	put_normal(char **split, char **env, int i, int *status);
int		check_unset(char *str);
char	*only_before_equal(char *str);
int		in_match(char *s1, char *s2);
t_env	*delete_list(t_env *env, int count);
t_env	*delete_in_env(t_env *env, char **splits);
char	**copy_all(t_env *take_env, char **env);
void	execut_command(char **env, char *str, int *check);
char	**take_it_all(char *s, int c);
char	*from_to(char *st, int i, int j);
int		find_how_many(char *s, char c);
char	*take_first_word(char *s);
t_meta	*split_it_all(char *str);
int		check_wich_command(char	*str);
char	*skip_first_word(char **str);
void	free_meta_struct(t_meta *meta);


#endif
