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

void		redirected_fork(t_meta *meta, t_assen assen, char **env, int fd);
void		redirect_output_fork(t_meta *meta, t_assen assen,
				char **env, int fd);
t_meta		*redirect_pipe(t_meta *meta, t_meta *temp,
				char **env, t_assen assen);
t_meta		*meta_input(t_meta *meta, t_meta *temp, int *on);
t_meta		*input_free(t_meta *meta);
int			input_conditions1(t_meta *meta, t_meta *temp);
char		**fill_split(char **split);
t_meta		*global_temp(t_meta *temp, t_assen assen, char **env, int fd);
t_meta		*redirect_temp(t_meta *temp, t_assen assen,
				char **env, t_meta *check);
t_support	output_support(t_meta *temp);
t_support	output_initializer(t_meta **temp, t_meta **check,
				t_meta *meta, t_support support);

#endif
