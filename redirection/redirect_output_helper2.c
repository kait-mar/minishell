/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_output_helper2.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molabhai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 16:44:30 by molabhai          #+#    #+#             */
/*   Updated: 2021/04/19 16:44:32 by molabhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	redirected_fork(t_meta *meta, t_assen assen, char **env, int fd)
{
	if (g_global.check_fd != -1)
	{
		dup2(g_global.check_fd, STDOUT_FILENO);
		close(g_global.check_fd);
	}
	if ((dup2(fd, STDIN_FILENO) != -1))
	{
		built_in(meta, assen, env);
		close(fd);
		exit(EXIT_SUCCESS);
	}
	else
	{
		ft_putstr(strerror(errno));
		close(fd);
		exit(EXIT_FAILURE);
	}
}

void	redirect_output_fork(t_meta *meta, t_assen assen, char **env, int fd)
{
	if ((dup2(fd, STDOUT_FILENO) != -1))
	{
		built_in(meta, assen, env);
		close(fd);
	}
	else
	{
		ft_putstr(strerror(errno));
		close(fd);
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}

t_meta	*return_value(t_support *support, t_meta *temp, char **env)
{
	*support = output_support(temp);
	temp = temp->next;
	temp->argument = chang_dollar_sign(temp->argument, env);
	if (ft_strcmp(temp->argument, "") == 0)
	{
		ft_printf("Ambiguos redirect \n");
		return (NULL);
	}
	return (temp);
}
