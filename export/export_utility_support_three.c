/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utility_support_three.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molabhai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 15:03:18 by molabhai          #+#    #+#             */
/*   Updated: 2021/04/15 15:03:20 by molabhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*space_take_only(char *str, int *i, int *space)
{
	int		j;
	char	*splits;

	j = *i;
	if (*space > 1)
	{
		j += 1;
		*space = 0;
	}
	while (((ft_isprint(str[j]) == 1) || str[j] == '=')
		&& (check_single_double_quote(str[j]) == 0))
		j += 1;
	splits = from_to(str, *i, j);
	*i = j;
	*space = 0;
	return (splits);
}

char	*take_only_loop(char *str, int *i, int *space)
{
	char	*splits;

	splits = NULL;
	if (str[*i] == ' ' && *i != 0)
		*space += 1;
	if (check_double_quotes(str[*i]))
		splits = filling_take_only(str, i);
	else if (check_single_quotes(str[*i]))
		splits = filling_take_only_second(str, i);
	else if ((ft_isprint(str[*i]) || *space > 1)
		&& (str[*i] != '\'' && str[*i] != '"'))
		splits = space_take_only(str, i, space);
	else if (str[*i] != '\0')
		*i += 1;
	return (splits);
}

int	check_single_double_quote(char c)
{
	if (c == '\"' || c == '\'')
		return (1);
	return (0);
}

int	check_single_quotes(char c)
{
	if (c == '\'')
		return (1);
	return (0);
}

int	check_double_quotes(char c)
{
	if (c == '\"')
		return (1);
	return (0);
}
