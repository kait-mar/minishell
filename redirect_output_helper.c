/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_output_helper.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kait-mar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 17:15:51 by kait-mar          #+#    #+#             */
/*   Updated: 2021/04/12 17:15:55 by kait-mar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

void	redirected_command(int fd, t_meta *meta, t_assen assen, char **env)
{
	int		pid;

	pid = fork();
	if (pid < 0)
		ft_putstr(strerror(errno));
	else if (pid == 0)
	{
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
	else
	{
		if ((waitpid(pid, g_global.status, WUNTRACED) == -1))
			ft_putstr(strerror(errno));
		close(fd);
	}
}

void	redirected_output_command(int fd, t_meta *meta, t_assen assen, char **env)
{
	int	pid;

	pid = fork();
	if (pid < 0)
		ft_putstr(strerror(errno));
	else if (pid == 0)
	{
		if ((dup2(fd, STDOUT_FILENO) != -1))
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
	else
	{
		if ((waitpid(pid, g_global.status, WUNTRACED) == -1))
			ft_putstr(strerror(errno));
		close(fd);
	}
}

int		redirect_command_head(int check_meta, int append, char *new)
{
	int	fd;

	if (append != 0)
	{
		if ((fd = open(new, O_CREAT | O_APPEND | O_RDWR, S_IRWXU)) == -1)
		{
			ft_printf("%s", strerror(errno));
			return (-1);
		}
	}
	else if (check_meta == '>')
	{
		if ((fd = open(new,  O_RDWR | O_CREAT | O_TRUNC, S_IRWXU)) < 0)
		{
			ft_putstr(strerror(errno));
			return (-1);
		}
	}
	return (fd);
}

char	*name_and_condition(char *new, int on, t_meta *meta, t_meta *temp)
{
	int i;
	return (NULL);
}