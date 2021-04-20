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

t_meta	*pipe_loop(t_meta *head, t_assen assen, char **env, int *count)
{
	pipe(g_global.fd);
	*count += 1;
	connecting(head, assen, env);
	close(g_global.fd[1]);
	g_global.in = g_global.fd[0];
	head = head->next;
	return (head);
}

t_meta	*pipe_last(t_meta *head, t_assen assen, char **env)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		close(g_global.fd[1]);
		if (head->next != NULL)
		{
			if (head->next->meta == '\0' || head->next->meta == ';')
				last_thing(head, assen, env);
		}
		last_thing(head, assen, env);
		exit(EXIT_SUCCESS);
	}
	close(g_global.fd[0]);
	close(g_global.fd[1]);
	close(g_global.in);
	return (head);
}
