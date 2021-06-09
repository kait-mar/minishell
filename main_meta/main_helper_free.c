/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_helper_free.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molabhai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 14:51:24 by molabhai          #+#    #+#             */
/*   Updated: 2021/04/26 14:51:38 by molabhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_head(t_meta *head)
{
	t_meta	*point;

	while (head != NULL)
	{
		point = head;
		if (head->argument)
			free(head->argument);
		head = head->next;
		free(point);
		point = NULL;
	}
}

void	free_temp(t_meta *head)
{
	if (head)
	{
		if (head->argument)
			free(head->argument);
		free(head);
		head = NULL;
	}
}

void	minishell_global(t_meta *head, t_assen assen, char **env)
{
	minishell_execution(head, assen, env);
	g_global.first_time = 1;
	if (g_global.in_redirect == 1)
	{
		g_global.in_redirect = 0;
		g_global.in_signal = 1;
	}
	else
		g_global.in_signal = 0;
}
