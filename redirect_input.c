/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kait-mar <kait-mar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 09:50:00 by kait-mar          #+#    #+#             */
/*   Updated: 2021/02/02 10:17:22 by kait-mar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_meta	*redirect_intput(t_meta *meta, char *str, char **env, int *status)
{
	int		fd;
	int		pid;
	t_meta	*temp;

	temp = meta;
	while (temp->next != NULL && temp->meta == '<')
	{
		temp = temp->next;
        temp->argument = chang_dollar_sign(temp->argument, env);
		if ((fd = open(temp->argument, O_RDWR, S_IRWXU)) < 0)
		{
			ft_putstr(strerror(errno));
			return (NULL);
		}
	}
	pid = fork();
	if (pid < 0)
		ft_putstr(strerror(errno));
	else if (pid == 0)
	{
		if ((dup2(fd, STDIN_FILENO) != -1))
		{
            built_in(meta, str, env, status, 0);
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
		if ((waitpid(pid, status, WUNTRACED) == -1))
			ft_putstr(strerror(errno));
		close(fd);
	}
	return (temp);
}
