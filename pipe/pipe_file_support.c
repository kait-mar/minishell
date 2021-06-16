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

t_meta	*pipe_loop_support(t_meta *head, char **env, t_assen assen)
{
	if (head->meta == '<')
	{
		head = redirect_intput(head, assen, env);
		while (head != NULL && head->meta == '|')
			head = head->next;
		if (head != NULL)
			head = head->next;
	}
	else if (head->meta == '>' && head->next->meta != 0)
	{
		if (g_global.in != 0)
		{
			dup2(g_global.in, 0);
			close(g_global.in);
		}
		head = redirect_output(head, assen, env);
		while (head != NULL && head->meta == '|')
			head = head->next;
		if (head != NULL)
			head = head->next;
	}
	return (head);
}

t_meta	*pipe_loop(t_meta *head, t_assen assen, char **env, int *count)
{
	pipe(g_global.fd);
	*count += 1;
	head->argument = chang_dollar_sign(head->argument, env);
	connecting(head, assen, env);
	close(g_global.fd[1]);
	if (g_global.in != 1)
		close(g_global.in);
	g_global.in = g_global.fd[0];
	if (g_global.redirect_fd != -1)
		head = head->next;
	g_global.redirect_fd = 0;
	g_global.redirect = 0;
	head = pipe_loop_support(head, env, assen);
	return (head);
}

t_meta	*pipe_last(t_meta *head, t_assen assen, char **env)
{
	pid_t	pid;

	red4();
	pid = fork();
	if (pid == 0)
	{
		close(g_global.fd[1]);
		if (head != NULL && head->next != NULL)
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
	close(g_global.in);
	return (head);
}
