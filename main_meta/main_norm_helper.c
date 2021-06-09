/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_norm_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molabhai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 12:02:44 by molabhai          #+#    #+#             */
/*   Updated: 2021/04/10 12:02:46 by molabhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	token_error(t_meta *head, int *status)
{
	t_meta	*a_head;

	a_head = head;
	while (a_head->next != NULL && a_head->next->meta != 0
		&& (ft_strcmp(a_head->argument, "") != 0
			|| ((a_head->meta == '>' || a_head->meta == '<')
				&& ft_strcmp(a_head->next->argument, "") == 0)))
		a_head = a_head->next;
	if (ft_strcmp(a_head->argument, "") == 0
		&& (a_head->meta == ';' || a_head->meta == '|')
		&& a_head->command == 0)
	{
		ft_printf("%s `%c'\n", ERROR_TOKEN, a_head->meta);
		*status = 258;
		return (1);
	}
	else if ((a_head->meta == '>' || a_head->meta == '<')
		&& (a_head->next == NULL || ft_strcmp(a_head->next->argument, "") == 0))
	{
		ft_printf("%s\n", ERROR_TOKEN_NL);
		*status = 258;
		return (1);
	}
	return (0);
}
