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


#ifndef MINISHELL_REDIRECTION_H
#define MINISHELL_REDIRECTION_H


typedef struct s_meta
{
	char	*argument;
	int		command;
	char	meta;
	int     meta_append;
	int     backslash;
	struct	s_meta	*next;
}				t_meta;

void	redirected_fork(t_meta *meta, t_assen assen, char **env, int fd);
void	redirect_output_fork(t_meta *meta, t_assen assen, char **env, int fd);

#endif
