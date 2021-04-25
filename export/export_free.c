/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molabhai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 14:18:46 by molabhai          #+#    #+#             */
/*   Updated: 2021/04/21 14:18:58 by molabhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_export_command(char **splits)
{
	int i;

	i = 0;
	if (splits == NULL)
		return;
	if (splits[i] != NULL)
	{
		while (splits[i])
		{
			free(splits[i]);
			splits[i] = NULL;
			i += 1;
		}
	}
	free(splits);
	splits = NULL;
}