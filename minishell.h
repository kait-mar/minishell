/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kait-mar <kait-mar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 17:29:54 by molabhai          #+#    #+#             */
/*   Updated: 2021/02/02 10:17:12 by kait-mar         ###   ########.fr       */
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
#include <signal.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
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
	char    **saver;
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
	int     meta_append;
	int     backslash;
	struct	s_meta	*next;
}				t_meta;

typedef struct  s_semi
{
    char    *command;
    struct s_meta *next;
}               t_semi;

/*	Metacharacter "Pipe" */

typedef struct s_pipe
{
    pid_t pid;
    int     index;
    int fd[2];
    struct s_pipe *next;
}               t_pipe;

typedef struct  s_std
{
    int in;
    int out;
    int index;
    struct  s_std *next;
}               t_std;

/* Buffer */

typedef struct s_buffer
{
    char **splits;
    int check;
}               t_buffer;

/*      Global Variables */

t_export *g_export;
int		g_process;
int     g_first_time;
int     g_in_signal;
pid_t   g_pid;
int     g_on;
int     g_in_line;
char    *g_old_pwd;
int     g_check_single_quote;
int     g_check_double_quote;

void	cd_command(char *argument, int *status, char **env);
char	**taking_command(char *str);
char	**split_to_tokens(char *str);
char	*reading_input(void);
char	*without_that(char *str, char c);
int		how_mutch_argument(char *str, int i);
char	*ft_toStrLower(char *str);
void 	pwd_command(int *status, int exept);
int		check_pwd(char *str, int *exept);
int		check_env(char *str);
void 	env_command(char **str, t_meta *meta, int *status);
void    export_command(char **env, char *splits, int *status, t_export *export);
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
t_export	*check_export(char **splits, char **env, t_export *export);
int		check_unset(char *str);
void	unset_command(char **env, char *str, int *status);
t_env		*filling_env(char **env);
t_env		*adding_last(t_env *head, int i, char *nv);
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
void	execut_command(char **env, char *str, int *check, int i, int *status);
char	**take_it_all(char *s, int c);
char	*from_to(char *st, int i, int j);
int		find_how_many(char *s, char c);
char	*take_first_word(char *s);
t_meta	*split_it_all(char *str);
int		check_wich_command(char	*str);
char	*skip_first_word(char **str);
void	free_meta_struct(t_meta *meta);
int		only_star(char *str);
void	stream_directory();
void    built_in(t_meta *meta, char *str, char **env, int *status, int i);
t_meta   *append_file(t_meta *meta, char *str, char **env, int *status);
int     check_append(char *s);
void    exit_command(long long status, char *s);
int     check_exit(char *str);
t_meta	*redirect_output(t_meta *meta, char *str, char **env, int *status);
t_meta	*redirect_intput(t_meta *meta, char *str, char **env, int *status);
t_meta      *pipe_file(t_meta *head, char *str, char **env, int *status);
void     my_putchar(char c);
void	signal_handler(int *status);
void	quit_signal(int signum);
void		inter_signal(int status);
void	prompt(int i);
void    filling_export(char **env);
void    export_realloc(void);
char    *split_to_last_cmd(char *str);
int     until_meta(char *str);
char    *chang_dollar_sign(char *string, char **env);
char	**take_only_carac_for_export(char *str);
char    *take_only(char *s);
int     check_double_inside_single(char *s);
int     check_single_inside_double(char *s);
char    *add_backslash(char *s);
int     in_it(char *s);
int     last_check(char *str, int i);
char    *error_reformulation(char *string);
int     check_equal(char *s);
char	*only_after_equal(char *str);

#endif