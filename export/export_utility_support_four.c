/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utility_support_four.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molabhai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 17:03:19 by molabhai          #+#    #+#             */
/*   Updated: 2021/04/15 17:03:23 by molabhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*from_to(char *str, int i, int j)
{
	char	*s;
	int		k;

	s = ft_calloc(sizeof(char), (j - i) + 1);
	if (!(s))
		return (NULL);
	k = 0;
	while (i < j)
	{
		s[k] = str[i];
		k += 1;
		i += 1;
	}
	s[k] = '\0';
	return (s);
}

int	ft_isprint_mod(int c)
{
	return (c > 32 && c <= 126);
}

char	**take_only_carac_for_export(char *str)
{
	int		i;
	char	**splits;
	int		k;

	i = 0;
	splits = ft_calloc(sizeof(char *), kait_count(str) + 2);
	if (!(splits))
		return (NULL);
	k = 0;
	while (str[i] != '\0')
	{
		if (ft_isprint(str[i]))
			splits[k++] = filling_first(str, &i);
		if (check_double_quotes(str[i]))
			splits[k++] = filling_quote_second(str, &i);
		if (check_single_quotes(str[i]))
			splits[k++] = filling_quote_third(str, &i);
		if (str[i] != '\0')
			i += 1;
	}
	return (splits);
}

char	**take_only_carac(char *str)
{
	int		i;
	char	**splits;
	int		k;
	int		space;

	i = 0;
	space = 0;
	splits = ft_calloc(sizeof(char *), kait_count(str) + 1);
	if (!(splits))
		return (NULL);
	k = 0;
	if (str[i] == ' ')
		space += 2;
	while (str[i] != '\0')
	{
		splits[k] = take_only_loop(str, &i, &space);
		if (splits[k] != NULL)
			k += 1;
	}
	return (splits);
}

void	free_splits(char **splits)
{
	int	i;

	i = 0;
	while (splits[i] != NULL)
	{
		free(splits[i]);
		splits[i] = NULL;
		i += 1;
	}
	free(splits);
	splits = NULL;
}
