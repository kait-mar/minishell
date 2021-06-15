/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utility_support_two.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molabhai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 14:37:05 by molabhai          #+#    #+#             */
/*   Updated: 2021/04/15 14:37:07 by molabhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*filling_first(char *str, int *i)
{
	int		j;
	char	*splits;

	j = *i;
	j = take_only_return(str, j);
	splits = from_to(str, *i, j);
	*i = j;
	return (splits);
}

char	*filling_quote_second(char *str, int *i)
{
	int		j;
	char	*splits;

	j = *i + 1;
	while (check_double_quotes(str[j]) == 0)
		j += 1;
	splits = from_to(str, *i, j + 1);
	*i = j;
	return (splits);
}

char	*filling_quote_third(char *str, int *i)
{
	int		j;
	char	*splits;

	j = *i + 1;
	while (check_single_quotes(str[j]) == 0)
		j += 1;
	splits = from_to(str, *i, j + 1);
	*i = j;
	return (splits);
}

char	*filling_take_only(char *str, int *i)
{
	char	*splits;
	int		j;

	j = *i + 1;
	while (check_double_quotes(str[j]) == 0 && str[j] != '\0')
		j += 1;
	if (str[j] == '\0')
	{
		splits = from_to(str, *i, j);
		*i = j;
		return (splits);
	}
	splits = from_to(str, *i, j + 1);
	*i = j + 1;
	return (splits);
}

char	*filling_take_only_second(char *str, int *i)
{
	int		j;
	char	*splits;

	j = *i + 1;
	while (check_single_quotes(str[j]) == 0 && str[j] != '\0')
		j += 1;
	if (str[j] == '\0')
	{
		splits = from_to(str, *i, j);
		*i = j;
		return (splits);
	}
	splits = from_to(str, *i, j + 1);
	*i = j + 1;
	return (splits);
}
