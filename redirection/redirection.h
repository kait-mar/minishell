/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molabhai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 17:05:50 by molabhai          #+#    #+#             */
/*   Updated: 2021/04/19 17:05:52 by molabhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTION_H
# define REDIRECTION_H

typedef struct s_meta
{
	char			*argument;
	int				command;
	char			meta;
	int				meta_append;
	int				backslash;
	struct s_meta	*next;
}				t_meta;

typedef struct s_support
{
	int	on;
	int	append;
	int	check_meta;
}				t_support;

typedef struct s_redirect
{
	int		fd;
	t_assen	*assen;
	t_meta	*check;
}			t_redirect;

typedef struct s_redirection
{
	int		fd;
	t_assen	assen;
}			t_redirection;

void		redirected_fork(t_meta *meta, t_assen assen, char **env, int fd);
void		redirect_output_fork(t_meta *meta, t_assen assen,
				char **env, int fd);
t_meta		*redirect_pipe(t_meta *meta, t_meta *temp,
				char **env, t_assen assen);
t_meta		*meta_input(t_meta *meta, t_meta *temp, int *on);
t_meta		*input_free(t_meta *meta);
int			input_conditions1(t_meta *meta, t_meta *temp);
char		**fill_split(char **split);
t_meta		*global_temp(t_meta *temp, t_redirection red,
				char **env, t_meta *meta);
t_meta		*redirect_temp(t_meta *temp, t_assen assen,
				char **env, t_meta *check);
t_support	output_support(t_meta *temp);
t_support	output_initializer(t_meta **temp, t_meta **check,
				t_meta *meta);
char		*fill_name(char *str, char *name);
int			check_redirect_error(char *new, int *fd, int append);
t_meta		*return_value(t_support *support, t_meta *temp, char **env);
t_meta		*red1(t_meta *meta, int *on);
t_meta		*red2(t_meta *temp, char **env);
t_meta		*red3(t_meta *meta, int fd);
void		red4(void);
t_meta		*independent_func(t_meta *temp, t_meta *meta, char **env);
char		*free_temp_(char *s);
void		checking_out(t_meta *temp, t_meta *meta, char **env, int *j);
t_meta		*ret_temp_in(t_meta *temp, t_assen assen, char **env, int j);
t_meta		*init_in(t_meta *meta, int *on, int *j);
t_meta		*pipe_in_loop(t_meta *temp, int fd);
t_meta		*ret_in_meta(t_meta *meta, t_meta *temp, int *on, int *fd);
t_meta		*input_conditions(t_meta *meta, char **new, t_meta *temp, int *on);

#endif
