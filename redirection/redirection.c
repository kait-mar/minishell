/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molabhai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 15:23:20 by molabhai          #+#    #+#             */
/*   Updated: 2021/06/16 15:23:24 by molabhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_meta	*ret_temp_in(t_meta *temp, t_assen assen, char **env, int j)
{
	if (j == 1 && temp->next != NULL)
	{
		while (temp->meta == '>')
			temp = temp->next;
	}
	if (temp->meta == '|')
	{
		g_global.redirect_fd = g_global.check_fd;
		temp = redirect_pipe(temp, temp, env, assen);
		while (temp->meta == '|')
			temp = temp->next;
	}
	close (g_global.check_fd);
	return (temp);
}

t_meta	*init_in(t_meta *meta, int *on, int *j)
{
	*j = 0;
	g_global.check_fd = -1;
	g_global.redirect_fd = -1;
	return (red1(meta, on));
}

t_meta	*pipe_in_loop(t_meta *temp, int fd)
{
	while (temp->meta == '|')
		temp = temp->next;
	close(fd);
	return (temp);
}

t_meta	*ret_in_meta(t_meta *meta, t_meta *temp, int *on, int *fd)
{
	char	*new;

	meta = input_conditions(meta, &new, temp, on);
	*fd = redirect_input_head(new);
	return (meta);
}
