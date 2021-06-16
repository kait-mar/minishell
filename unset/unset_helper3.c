/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_helper3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molabhai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 11:13:55 by molabhai          #+#    #+#             */
/*   Updated: 2021/06/14 11:13:56 by molabhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_unset_tok(char *string)
{
	int	i;

	i = 0;
	while (string[i] != '\0')
	{
		if (ft_isalnum(string[i]) == FALSE)
		{
			write(2, "unset syntax error\n", 19);
			*(g_global.status) = 1;
			return (1);
		}
		i += 1;
	}
	return (0);
}
