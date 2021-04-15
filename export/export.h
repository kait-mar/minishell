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
#define EXPORT_H

typedef struct s_export
{
	char	*command;
	char	**saver;
	char 	**argument;
	char	**env;
	int		flag;
}				t_export;

int 	last_check_first(char *str, int i);
int 	last_check_second(char *str, int i);
int 	last_check_third(char *str, int i);
void 	match_free(char *env, char *new_argument);
int		ft_isprint_mod(int c);
int		take_only_return(char *str, int j);
char	*filling_first(char *str, int *i);
char	*filling_quote_second(char *str, int *i);
char	*filling_take_only(char *str, int *i);
char	*filling_quote_third(char *str, int *i);
char	*filling_take_only_second(char *str, int *i);
char	*space_take_only(char *str, int *i, int *space);
char	*take_only_loop(char *str, int *i, int *space);
void	filling_global(t_export *tmp);
t_export	*filling_tmp(void);
int		return_env_on(char *str);
t_export *check_export_init(char **splits, t_export *export);
char		*split_reformulation(char *splits);
t_export	*put_in_export(char *splits, int *on, t_export *export);
t_export	*export_loop(char *splits, t_export *export, int on, int j);
int		no_space(char *s);
t_export	*export_global(t_export *export);
void 	filling_export_env(char **env, char *export_argument);
void	printing_filling_env(t_export *export, int *status, char **env);

#endif