/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molabhai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 17:23:07 by molabhai          #+#    #+#             */
/*   Updated: 2021/04/15 17:23:12 by molabhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPORT_H
# define EXPORT_H

typedef struct s_export
{
	char	*command;
	char	**saver;
	char	**argument;
	char	**env;
	int		flag;
}				t_export;

int			last_check_first(char *str, int i);
int			last_check_second(char *str, int i);
int			last_check_third(char *str, int i);
void		match_free(char *env, char *new_argument);
int			ft_isprint_mod(int c);
int			take_only_return(char *str, int j);
char		*filling_first(char *str, int *i);
char		*filling_quote_second(char *str, int *i);
char		*filling_take_only(char *str, int *i);
char		*filling_quote_third(char *str, int *i);
char		*filling_take_only_second(char *str, int *i);
char		*space_take_only(char *str, int *i, int *space);
char		*take_only_loop(char *str, int *i, int *space);
void		filling_global(t_export *tmp);
t_export	*filling_tmp(void);
int			return_env_on(char *str);
t_export	*check_export_init(char **splits, t_export *export);
char		*split_reformulation(char *splits);
t_export	*put_in_export(char *splits, int *on, t_export *export);
t_export	*export_loop(char *splits, t_export *export, int on, int *j);
int			no_space(char *s);
t_export	*export_global(t_export *export);
void		filling_export_env(char **env, char *export_argument);
void		printing_filling_env(t_export *export, char **env);
char		*return_adding_quote(char *s, int j);
char		*return_loc(char *s, char *s2, char *str);
void		print_count(char *str, int *i, int *count);
void		double_quote_count(char *str, int *i, int *count);
void		single_quote_count(char *str, int *i, int *count);
void		pwd_init(int *i);
char		*append(char *s1, char *s2);
void		shlvl_init(int *i);
void		pwd_env(char *s, char **env, int *i);
void		shlvl_env(char **env, int *i);
char		*findin_env(char **env);
void		start_env(char **env, int *i);
void		export_init(void);
void		env_init(char **env);
int			fill_env_init(char **env, int *pwd, int *shlvl, int *start);
void		filling_export(char **env);
void		free_export_command(char **splits);
char		*take_before_equal(char *str);
void		free_global_exp(char *splits, int k);
char		*return_alloc_env(char *str);
void		fill_shlvl(char **ss, char **env, int i, int *shlvl);
void		fill_pwd(char **ss, int i, int *pwd);
char		*front_add_helper(char *s, char *to_append, int *i);
int			alpha(char *s);

#endif