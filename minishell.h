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
# define MINISHELL_H
# define TRUE 1
# define FALSE 0
# define BUFFER 3
# define ERROR_TOKEN "minishell: syntax error near unexpected token"
# define ERROR_TOKEN_NL "minishell:syntax error near unexpected token `newline'"
# define SHLVL_ERROR "minishell: warning: shell level "
# define EXIT_ERROR "minishell: exit: "

# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/types.h>
# include <dirent.h>
# include <unistd.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <stdint.h>
# include <term.h>
# include "./Libft/libft.h"
# include "./echo/echo.h"
# include "./bash_history/bash_history.h"
# include "./export/export.h"
# include "./escape_character/escape_character.h"
# include "./executable/executable.h"
# include "./unset/unset.h"
# include "./minishell_utils/minishell_utils.h"
# include "./redirection/redirection.h"
# include "./dollar_sign/dollar_sign.h"

typedef struct s_minishell
{
	t_meta		*meta;
	t_meta		*head;
	t_meta		*global;
	char		*str;
	char		*string;
}				t_minishell;

typedef struct s_command_cd
{
	char	*command;
	char	*argument;
	int		wich_path;
	int		error;
}				t_command_cd;

typedef struct s_unset
{
	char			*argument;
	struct s_unset	*next;
}				t_unset;

typedef struct s_spaces
{
	char	*bult;
	int		spaces;
}			t_spaces;
/*	Metacharacter "Semicolon" */
typedef struct s_semi
{
	char			*command;
	struct s_meta	*next;
}				t_semi;

/*	Metacharacter "Pipe" */

typedef struct s_pipe
{
	pid_t			pid;
	int				index;
	int				fd[2];
	struct s_pipe	*next;
}				t_pipe;

typedef struct s_std
{
	int				in;
	int				out;
	int				index;
	struct s_std	*next;
}				t_std;

typedef struct s_buffer
{
	char	**splits;
	int		check;
}				t_buffer;

struct s_global
{
	int			j_echo;
	int			e_quote;
	int			tt;
	int			on;
	int			from_in;
	int			check_fd;
	int			process;
	int			in_signal;
	int			redirect;
	int			only_in_space;
	int			redirect_fd;
	int			s_status;
	int			first_time;
	int			check_single_quote;
	int			check_double_quote;
	int			pwd_on;
	int			in_redirect;
	char		*pwd_only;
	char		*old_pwd;
	char		*buffer;
	int			oldpwd_on;
	char		*oldpwd_only;
	int			check;
	int			*status;
	int			in;
	int			fd[2];
	int			signal_input;
	char		*buffer_address;
	int			old_save;
	t_export	*export;
}			g_global;

void		cd_command(char *argument, int *status, char **env);
char		**taking_command(char *str);
char		**split_to_tokens(char *str);
char		*without_that(char *str, char c);
int			how_mutch_argument(char *str, int i);
char		*ft_toStrLower(char *str);
void		pwd_command(int *status, int exept);
int			check_pwd(char *str);
int			check_env(char *str);
void		env_command(char **str, t_meta *meta, int *status);
void		export_command(char **env, char *splits,
				t_export *export);
int			how_mutch_arguments(char **splits, int i);
int			check_exp_lex(char *str);
int			match(char *str, char *export);
int			arguments_in(char **splits, int i);
void		free_export(t_export *export);
char		**take_only_carac(char *str);
int			check_quote(char *str);
int			check_double_quote(char *str);
void		free_splits(char **splits);
char		*front_append(char *string, char *to_append);
t_export	*check_export(char **splits, t_export *export);
int			check_unset(char *str);
void		unset_command(char **env, char *str, int *status);
t_env		*filling_env(char **env);
t_env		*adding_last(t_env *head, int i, char *nv);
int			kait_count(char *str);
int			check_single_quotes(char c);
int			check_double_quotes(char c);
int			check_single_double_quote(char c);
void		ft_putstr(char *s);
int			print(char **bult, int *status);
int			find(char *str, char c);
void		quote_dquote(char *line);
int			echo(char *argv, char **env, int *status);
int			ft_strcmp(const char *s1, const char *s2);
char		**keep_split(char *s, char c, char b);
int			print_env(char *bult, char **env, int which_quote, int *status);
int			echo_strcmp(char *s1, char *s2);
void		put_cases(char **bult, char **env, int *status);
void		put_normal(char **split, int i, int *status);
int			check_unset(char *str);
char		*only_before_equal(char *str);
int			in_match(char *s1, char *s2);
t_env		*delete_list(t_env *env, int count);
t_env		*delete_in_env(t_env *env, char **splits, int i);
char		**copy_all(t_env *take_env, char **env);
void		execut_command(char **env, char *str, int *status);
char		**take_it_all(char *s, int c);
char		*from_to(char *st, int i, int j);
int			find_how_many(char *s, char c);
char		*take_first_word(char *s);
t_meta		*split_it_all(char *str, t_meta *global);
int			check_wich_command(char	*str);
char		*skip_first_word(char *str);
void		free_meta_struct(t_meta *meta);
int			only_star(char *str);
void		stream_directory(void);
void		built_in(t_meta *meta, t_assen assen, char **env);
int			check_append(char *s);
void		exit_command(int *status, char *s);
int			check_exit(char *str);
t_meta		*redirect_output(t_meta *meta, t_assen assen,
				char **env);
t_meta		*redirect_intput(t_meta *meta, t_assen assen,
				char **env);
t_meta		*pipe_file(t_meta *head, t_assen assen,
				char **env);
void		my_putchar(char c);
void		signal_handler(void);
void		quit_signal(int signum);
void		inter_signal(int status);
void		prompt(void);
void		export_realloc(void);
char		*split_to_last_cmd(char *str);
int			until_meta(char *str);
char		*chang_dollar_sign(char *string, char **env);
char		**take_only_carac_for_export(char *str);
char		*take_only(char *s);
int			check_double_inside_single(char *s);
int			check_single_inside_double(char *s);
char		*add_backs(char *s);
int			in_it(char *s);
int			last_check(char *str, int i);
char		*error_reformulation(char *string);
int			check_equal(char *s);
char		*only_after_equal(char *str);
int			how_many_escape(char *bult);
int			find_dollar_esacpe(char *bult);
int			find_without(char *bult, char c);
char		*trim_once(char *s1);
int			check_shlvl(char *s);
char		*remove_staring_quote(const char *s);
char		*file_name(char *str);
char		*final_file_name(char *file);
char		*escape_normal(char *str);
int			check_escape_meta(char *str, int i);
int			active(char *str, int i);
char		*escape_meta(char *str);
char		*remove_space(char *string);
int			check_escape_space(char *string, int i);
char		*remove_escape_dollar(char *s);
int			check_escape_dollar(char *str, int i);
int			homogene(char *s);
int			flag_strcmp(char *s1);
char		*trim_once_left(char *s);
char		*rm_space_variable(char *s, int wich);
int			inside_quotes(char *s, int i);
int			escape_front_true(char *s, int i);
char		*add_front_space(char *s);
int			escape_back_true(char *s, int i);
char		*add_back_space(char *s);
int			check_inside_back_quote(char *s, int i);
int			check_inside_front_quote(char *s, int i);
char		*take_first_word_re(char *s);
char		*return_parsed(char **changes, char **env);
char		*ft_strjoin_re(char const *s1, char const *s2);
int			check_bin_echo(char *str);
char		*print_env1(char *bult);
char		*print_env2(char *bult, char **env, int which_quote);
int			print_envir(char **str, char **env, char **tabs);
char		*check_print(char *bult);
char		**put_cases1(char **bult);
t_assen		minishell_init(char **env);
int			token_error(t_meta *head, int *status);
void		minishell_execution(t_meta *head, t_assen assen, char **env);
void		minishell(char **av, char **env, t_assen assen);
int			check_append(char *s);
t_meta		*meta_in(char **splits, t_meta *global, int *i);
t_meta		*meta_out(char **splits, t_meta *global, int *i);
t_meta		*meta_in_between(char **splits, t_meta *temp, int *i);
t_meta		*meta_out_between(char **splits, t_meta *temp, int *i);
t_meta		*split_it_all_loop(char **splits, t_meta *global, int i);
int			skip_quote(char *str, int *i);
char		*filling_split(char *str, int *i, int *j);
int			valid(char *str, int j, int len);
int			return_count_meta(char *str, int *i, int count, int *how_mutch);
void		redirected_command(int fd, t_meta *meta, t_assen assen, char **env);
void		redirected_output_command(int fd, t_meta *meta,
				t_assen assen, char **env);
int			redirect_command_head(int check_meta, int append, char *new);
t_meta		*name_and_condition(char **new, int *on,
				t_meta *meta, t_meta *temp);
int			redirect_input_head(char *new);
t_meta		*input_conditions(t_meta *meta, char **new, t_meta *temp, int *on);
char		*rm_space_helper(int *i, char *s, int *j, int wich);
int			return_loop(int i, char *s);
int			only_space(char *s, int i);
int			count_space_variable(char *s);
void		old_pwd(char **env);
void		new_pwd(char **env, char *str);
int			find_pwd(char *s);
int			find_old_pwd(char *s);
void		remove_old_pwd(char **env);
char		*add_in(char *first, char *second);
int			check_only_single_double(char *s);
char		*old_pwd_helper(char **env, int i);
char		*old_pwd_support(void);
int			cd_command_helper(int *status, char **env,
				char **s, int first_time);
void		cd_command_helper2(char **env, int *first_time);
int			escape_front_true(char *s, int i);
char		*chang_dollar_sign(char *str, char **env);
int			inside_quotes(char *s, int i);
char		*rm_space_variable(char *s, int wich);
char		*take_only_helper(char *s, int i);
char		*take_only_helper2(char *s, int i, char ref);
char		*take_only_helper3(char *s);
char		*take_only_core(char *s, int i);
void		filling_history(int fd, t_assen *move);
int			check_is_num(char *s);
long long	ft_atois(const char *str);
void		last_things(char *s, int *status);
int			connecting(t_meta *head, t_assen assen, char **env);
t_meta		*pipe_loop(t_meta *head, t_assen assen, char **env, int *count);
int			last_thing(t_meta *head, t_assen assen, char **env);
t_meta		*pipe_last(t_meta *head, t_assen assen, char **env);
void		free_head(t_meta *head);
void		free_temp(t_meta *head);
int			redirect_true(t_meta *head);
int			go_nexts(char str);
long long	results(char *str, int neg, int i, int res);
char		*cd_free(char *s, char *ss, char **env);
int			new_pwd_core(char **env, int *i, char *oldpwd, int *res);
char		*old_pwd_core(char **env, int *i, int *j);
int			pwd_core(char **env, int *i, char *old_pwd, int *res);
t_meta		*meta_out_between_core(t_meta *temp, char *splits);
int			d_quotes(char *str, int i, char c);
char		**splits_by_meta(char *str);
int			exit_command_void(int *status, char *s);
t_meta		*split_it_header(char **splits, t_meta *global, int *i);
int			check_meta(char *str);
char		*remove_space_core(char *str, char *string, int *j, int *start);
t_meta		*minishell_helper(t_meta *meta,
				char **str, t_meta *global);
void		minishell_global(t_meta *head, t_assen assen,
				char **env);
int			match_shlvl(char *env, char *sh);
t_meta		*initialize_temp(void);
t_minishell	mini_shell(void);

#endif