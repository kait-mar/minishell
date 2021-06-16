/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kait-mar <kait-mar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 14:22:30 by molabhai          #+#    #+#             */
/*   Updated: 2021/01/20 10:39:58 by kait-mar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	connecting(t_meta *head, t_assen assen, char **env)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		close(g_global.fd[0]);
		if (g_global.in == -1)
			exit(EXIT_FAILURE);
		if (g_global.in != 0 && g_global.tt == 0)
		{
			dup2(g_global.in, 0);
			close(g_global.in);
		}
		if (g_global.fd[1] != 1)
		{
			dup2(g_global.fd[1], 1);
			close(g_global.fd[1]);
		}
		if (check_bin_echo(head->argument) == 1)
			head->command = 6;
		built_in(head, assen, env);
		exit(EXIT_SUCCESS);
	}
	return (pid);
}

int	last_thing(t_meta *head, t_assen assen, char **env)
{
	if (g_global.in > 0 && g_global.tt == 0)
	{
		dup2(g_global.in, 0);
		close(g_global.in);
	}
	if (head->meta == '>')
	{
		head = redirect_output(head, assen, env);
		while (head->meta == '|')
			head = head->next;
	}
	else
	{
		head->argument = chang_dollar_sign(head->argument, env);
		built_in(head, assen, env);
	}
	return (0);
}

int	pipe_condition(t_meta *head)
{
	return (head->next != NULL
		&& (head->next->meta == '\0' || head->next->meta == '|'
			|| head->next->meta == ';' || head->next->meta == '<'
			|| head->next->meta == '>'));
}

t_meta	*pipe_file_core(t_meta *head)
{
	head = head->next;
	while (head->meta == '|')
		head = head->next;
	if (head->next != NULL)
		head = head->next;
	return (head);
}

t_meta	*pipe_file(t_meta *head, t_assen assen, char **env)
{
	int	count;

	count = 0;
	g_global.old_save = dup(STDIN_FILENO);
	if (g_global.redirect == 1)
		g_global.in = g_global.redirect_fd;
	else
		g_global.in = 1;
	pipe(g_global.fd);
	g_global.in_redirect = 0;
	while (head != NULL && (head->meta == '|' || g_global.redirect == 1))
	{
		if (pipe_condition(head))
			head = pipe_loop(head, assen, env, &count);
		else
			break ;
	}
	head = pipe_last(head, assen, env);
	while (count-- >= 0)
		wait3(NULL, WUNTRACED, NULL);
	dup2(g_global.old_save, 0);
	close(g_global.old_save);
	if (head != NULL && head->meta == '>')
		head = pipe_file_core(head);
	return (head);
}
