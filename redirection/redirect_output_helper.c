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
	else
	{
		if ((waitpid(pid, g_global.status, WUNTRACED) == -1))
			ft_putstr(strerror(errno));
		close(fd);
	}
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
	else
	{
		if ((waitpid(pid, g_global.status, WUNTRACED) == -1))
			ft_putstr(strerror(errno));
		close(fd);
	}
}

int	redirect_command_head(int check_meta, int append, char *new)
{
	int	fd;

	fd = 0;
	if (append != 0)
	{
		fd = open(new, O_CREAT | O_APPEND | O_RDWR, S_IRWXU);
		if ((fd) == -1)
		{
			ft_printf("%s", strerror(errno));
			return (-1);
		}
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
	*new = file_name(temp->argument);
	temp->argument = temp->argument + ft_strlen(*new);
	if (*(temp->argument) == ' ')
		(temp->argument)++;
	if (meta->command == 0
		&& check_wich_command(take_first_word(temp->argument)) != 0 && *on == 0)
	{
		meta = temp;
		meta->command = check_wich_command(take_first_word(temp->argument));
		*on = 1;
	}
	*new = final_file_name(*new);
	if (*on == 0)
	{
		if (ft_strcmp(meta->argument, "") != 0
			&& ft_strcmp(temp->argument, "") != 0
			&& (meta->argument[ft_strlen(meta->argument) - 1] != ' '
				&& *(temp->argument) != ' '))
			meta->argument = ft_strjoin(meta->argument, " ");
		meta->argument = ft_strjoin(meta->argument, temp->argument);
	}
	return (meta);
}

int	redirect_input_head(char *new)
{
	int	fd;

	fd = open(new, O_RDWR, S_IRWXU);
	if ((fd) < 0)
	{
		g_in_redirect = 1;
		ft_printf("minishell: %s: %s", new, strerror(errno));
		return (-1);
	}
	return (fd);
}
