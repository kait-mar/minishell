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
#define BUFFER 3
#define ERROR_TOKEN "minishell: syntax error near unexpected token"
#define ERROR_TOKEN_NL "minishell: syntax error near unexpected token `newline'"

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
#include <sys/wait.h>
#include <stdint.h>
#include <term.h>
#include "./Libft/libft.h"
#include "./echo/echo.h"
#include "./bash_history/bash_history.h"


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

struct s_global
{
    int on;
    int in_signal;
    int first_time;
    int check_single_quote;
    int check_double_quote;
    int pwd_on;
    char    *pwd_only;
    char    *old_pwd;
    int oldpwd_on;
    char *oldpwd_only;
    int check;
    int *status;
}       g_global;


/*      Global Variables */

t_export *g_export;
int		g_process;
int     g_first_time;
int     g_in_signal;
int		g_in_redirect;
pid_t   g_pid;
int     g_on;
int     g_in_line;
char    *g_old_pwd;
int     g_check_single_quote;
int     g_check_double_quote;
char    *g_pwd_only;
char    *g_oldpwd_only;
int     g_pwd_on;
int     g_oldpwd_on;
int     g_check;

void	cd_command(char *argument, int *status, char **env);
char	**taking_command(char *str);
char	**split_to_tokens(char *str);
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
int		echo_strcmp(char *s1, char *s2);
void	put_cases(char **bult, char **env, int *status);
void	put_normal(char **split, char **env, int i, int *status);
int		check_unset(char *str);
char	*only_before_equal(char *str);
int		in_match(char *s1, char *s2);
t_env	*delete_list(t_env *env, int count);
t_env	*delete_in_env(t_env *env, char **splits, int i, int *status);
char	**copy_all(t_env *take_env, char **env);
void	execut_command(char **env, char *str, int *status);
char	**take_it_all(char *s, int c);
char	*from_to(char *st, int i, int j);
int		find_how_many(char *s, char c);
char	*take_first_word(char *s);
t_meta	*split_it_all(char *str, char **env);
int		check_wich_command(char	*str);
char	*skip_first_word(char **str);
void	free_meta_struct(t_meta *meta);
int		only_star(char *str);
void	stream_directory();
void    built_in(t_meta *meta, t_assen assen, char **env, int *status);
int     check_append(char *s);
void    exit_command(int *status, char *s, t_assen *assen);
int     check_exit(char *str);
t_meta	*redirect_output(t_meta *meta, t_assen assen, char **env, int *status);
t_meta	*redirect_intput(t_meta *meta, t_assen assen, char **env, int *status);
t_meta      *pipe_file(t_meta *head, t_assen assen, char **env, int *status);
void     my_putchar(char c);
void	signal_handler(int *status);
void	quit_signal(int signum);
void		inter_signal(int status);
void	prompt(void);
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
int		how_many_escape(char *bult);
int		find_dollar_esacpe(char *bult, char c);
int		find_without(char *bult, char c);
char	*trim_once(char *s1);
int     check_shlvl(char *s);
char	*ft_strtrim2(char const *s, char const *set);
char    *remove_staring_quote(const char *s);
char    *file_name(char *str);
char	*final_file_name(char *file);
char    *escape_normal(char *str);
int     check_escape_meta(char *str, int i);
int     active(char *str, int i);
char    *escape_meta(char *str);
char    *remove_space(char *string);
int     check_escape_space(char *string, int i);
char    *remove_escape_dollar(char *s);
int     check_escape_dollar(char *str, int i);
int		homogene(char *s);
int	    flag_strcmp(char *s1, char *s2);
char	*trim_once_left(char *s);
char    *rm_space_variable(char *s, int wich);
int     inside_quotes(char *s, int i);
int    escape_front_true(char *s, int i);
char    *add_front_space(char *s);
int    escape_back_true(char *s, int i);
char    *add_back_space(char *s);
int     check_inside_back_quote(char *s, int i);
int     check_inside_front_quote(char *s, int i);
char    *take_first_word_re(char *s);
char    *return_parsed(char **changes, char **env);
char	*ft_strjoin_re(char const *s1, char const *s2);
int     check_bin_echo(char *str);
char    *print_env1(char *bult);
char    *print_env2(char *bult, char **env, int which_quote, int *status);
int		print_envir(char **str, char **env, char **tabs);
char    *check_print(char *bult);
char	**put_cases1(char **bult);
t_assen   minishell_init(char **env);
int   token_error(t_meta *head, int *status);
void minishell_execution(t_meta *head, t_assen assen, char **env);
void    minishell(char **av, char **env, t_assen assen);
int     check_append(char *s);
t_meta      *meta_in(char **splits, t_meta *global, int *i);
t_meta	*meta_out(char **splits, t_meta *global, int *i);
t_meta	*meta_in_between(char **splits, t_meta *temp, int *i);
t_meta 	*meta_out_between(char **splits, t_meta *temp, int *i);
t_meta 	*split_it_all_loop(char **splits, t_meta *global, int i);
int 	skip_quote(char *str, int *i);
char 	*filling_split(char *str, int *i, int *j);
int     valid(char *str, int j, int len);
int		return_count_meta(char *str, int *i, int count, int *how_mutch);

#endif