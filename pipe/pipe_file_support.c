/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_file_support.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molabhai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 15:21:08 by molabhai          #+#    #+#             */
/*   Updated: 2021/04/19 15:21:10 by molabhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int 	redirect_true(t_meta *head)
{
	while (head->meta == '|')
		head = head->next;
	if (head->meta == '<')
		return (1);
	return (0);
}

t_meta	*pipe_loop(t_meta *head, t_assen assen, char **env, int *count)
{
	int	i;

	i = 0;
	pipe(g_global.fd);
	*count += 1;
	connecting(head, assen, env);
	close(g_global.fd[1]);
	g_global.in = g_global.fd[0];
	if (g_global.redirect == 1)
	{
		while (i < 2 && head->next != NULL)
		{
			head = head->next;
			i += 1;
		}
		g_global.redirect = 0;
	}
	else
		head = head->next;
	if (head->meta == '<')
	{
		head = redirect_intput(head, assen, env, g_global.status);
		while (head->meta == '|')
			head = head->next;
		head = head->next;
	}
	else if (head->meta == '>')
	{
		head = redirect_output(head, assen, env, g_global.status);
		while (head->meta == '|')
			head = head->next;
		head = head->next;
	}
	return (head);
}

t_meta	*pipe_last(t_meta *head, t_assen assen, char **env)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		close(g_global.fd[1]);
		if (head->next != NULL && head != NULL)
		{
			if (head->next->meta == '\0' || head->next->meta == ';')
				last_thing(head, assen, env);
		}
		else if (head != NULL)
			last_thing(head, assen, env);
		exit(EXIT_SUCCESS);
	}
	close(g_global.fd[0]);
	close(g_global.fd[1]);
	close(g_global.redirect_fd);
	close(g_global.in);
	return (head);
}
