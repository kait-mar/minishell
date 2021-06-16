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

#include "../minishell.h"

void	redirected_command(int fd, t_meta *meta, t_assen assen, char **env)
{
	int		pid;

	pid = fork();
	if (pid < 0)
		ft_putstr(strerror(errno));
	else if (pid == 0)
		redirected_fork(meta, assen, env, fd);
	if ((waitpid(pid, g_global.status, WUNTRACED) == -1))
		ft_putstr(strerror(errno));
	close(fd);
}

void	redirected_output_command(
			int fd, t_meta *meta, t_assen assen, char **env)
{
	int	pid;

	pid = fork();
	if (pid < 0)
		ft_putstr(strerror(errno));
	else if (pid == 0)
		redirect_output_fork(meta, assen, env, fd);
	else if ((waitpid(pid, g_global.status, WUNTRACED) == -1))
		ft_putstr(strerror(errno));
}

int	redirect_command_head(int check_meta, int append, char *new)
{
	int	fd;

	fd = 0;
	if (g_global.in_redirect == 1 || append != 0)
	{
		if (check_redirect_error(new, &fd, append) == -1)
			return (-1);
	}
	else if (check_meta == '>')
	{
		fd = open(new, O_RDWR | O_CREAT | O_TRUNC, S_IRWXU);
		if ((fd) < 0)
		{
			ft_putstr(strerror(errno));
			return (-1);
		}
	}
	return (fd);
}

t_meta	*name_and_condition(char **new, int *on, t_meta *meta, t_meta *temp)
{
	char	*str;

	*new = file_name(temp->argument);
	str = temp->argument;
	temp->argument = ft_strdup(temp->argument + ft_strlen(*new));
	free(str);
	if ((temp->argument)[0] == ' ' && only_space(temp->argument, 0) == 0)
	{
		str = temp->argument;
		temp->argument = ft_strdup(temp->argument + 1);
		free(str);
	}
	meta = meta_input(meta, temp, on);
	*new = final_file_name(*new);
	if (*on == 0)
	{
		if (input_conditions1(meta, temp))
			meta = input_free(meta);
		str = meta->argument;
		meta->argument = ft_strjoin(meta->argument, temp->argument);
		free(str);
	}
	temp->argument = free_temp_(temp->argument);
	return (meta);
}

int	redirect_input_head(char *new)
{
	int	fd;

	fd = open(new, O_RDWR, S_IRWXU);
	if ((fd) < 0)
	{
		g_global.in_redirect = 1;
		ft_printf("minishell: %s: %s\n", new, strerror(errno));
		return (-1);
	}
	return (fd);
}
