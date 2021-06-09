/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utility_support_five.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molabhai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 17:05:35 by molabhai          #+#    #+#             */
/*   Updated: 2021/04/15 17:05:36 by molabhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*error_reformulation(char *string)
{
	int		i;
	int		j;
	char	*s;

	i = 0;
	j = 0;
	s = ft_calloc(sizeof(char), ft_strlen(string) + 1);
	if (!(s))
		return (NULL);
	while (string[i] != '\0')
	{
		if (string[i] == '\\' && string[i - 1] != '\\' && i > 0)
			i += 1;
		else
		{
			s[j] = string[i];
			j += 1;
			i += 1;
		}
	}
	s[j] = '\0';
	free(string);
	return (s);
}

int	check_single_inside_double(char *s)
{
	int	i;
	int	first;

	i = 0;
	first = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\'')
			first = 1;
		else if (s[i] == '\"' && first == 0)
		{
			i += 1;
			while (s[i] != '\"' && s[i] != '\0')
			{
				if (s[i] == '\'')
					return (1);
				i++;
			}
		}
		i++;
	}
	return (0);
}

int	check_double_inside_single(char *s)
{
	int	i;
	int	first;

	i = 0;
	first = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\"')
			first = 1;
		else if (s[i] == '\'' && first == 0)
		{
			i += 1;
			while (s[i] != '\'' && s[i] != '\0')
			{
				if (s[i] == '\"')
					return (1);
				i++;
			}
		}
		i++;
	}
	return (0);
}
