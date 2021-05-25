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
		if (g_global.in != 0)
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

int		last_thing(t_meta *head, t_assen assen, char **env)
{
	if (g_global.in != 0)
	{
		dup2(g_global.in, 0);
		close(g_global.in);
	}
	if (head->meta == '>')
	{
		head = redirect_output(head, assen, env, g_global.status);
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

t_meta	*pipe_file(t_meta *head, t_assen assen, char **env, int *status)
{
	int		count;
	int		old_stdin;

	count = 0;
	old_stdin = dup(STDIN_FILENO);
	if (g_global.redirect == 1)
		g_global.in = g_global.redirect_fd;
	else
		g_global.in = 1;
	while (head != NULL && (head->meta == '|' || g_global.redirect == 1))
	{
		if (head->next->meta == '\0' || head->next->meta == '|'
			|| head->next->meta == ';' || head->next->meta == '<'
			|| head->next->meta == '>')
			head = pipe_loop(head, assen, env, &count);
		else
			break ;
	}
	head = pipe_last(head, assen, env);
	while (count-- >= 0)
		wait3(NULL, WUNTRACED, NULL);
	dup2(old_stdin, 0);
	close(old_stdin);
	if (head->meta == '>')
	{
		head = head->next;
		while (head->meta == '|')
			head = head->next;
		if (head->next != NULL)
			head = head->next;
	}
	return (head);
}
