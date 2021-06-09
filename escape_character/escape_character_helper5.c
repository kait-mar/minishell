/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escape_character_helper5.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kait-mar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 17:08:56 by kait-mar          #+#    #+#             */
/*   Updated: 2021/04/17 17:08:58 by kait-mar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_dollar_core(char *s, int count, int *i)
{
	int	nb_escape;

	nb_escape = 0;
	while (s[*i] == '\\')
	{
		*i += 1;
		nb_escape += 1;
	}
	if (s[*i] == '$')
	{
		*i += 1;
		count += 1;
	}
	count += nb_escape % 2;
	return (count);
}

void	remove_escape_dollar_support(char **str, char *s, int *i, int *j)
{
	(*str)[(*j)++] = s[(*i)++];
	while (s[*i] == '\\')
	{
		*i += 1;
		(*str)[(*j)++] = s[(*i)++];
	}
	(*str)[(*j)++] = s[(*i)++];
}

void	escape_core_support(char *str, char **string, int *i, int *j)
{
	if (in_quote(str, *i) == 1)
	{
		while (str[*i] != '"' && str[*i] != '\'')
			(*string)[(*j)++] = str[(*i)++];
		if (str[*i] == '"' || str[*i] == '\'')
			(*string)[(*j)++] = str[(*i)++];
	}
	else
	{
		*i += 1;
		(*string)[(*j)++] = str[(*i)++];
	}
}

int	es_count(char *s, int count)
{
	int	i;
	int	j;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\\')
		{
			j = 0;
			while (s[i] == '\\')
			{
				j += 1;
				i += 1;
			}
			if ((j % 2) == 0)
				count += (j / 2);
			else
				count += (j / 2) + 1;
		}
		else
			count += 1;
		i += 1;
	}
	return (count);
}

char	*es_for_quote(char *s)
{
	int		i;
	int		count;
	int		j;
	char	*str;

	j = 0;
	i = 0;
	count = 0;
	str = (char *) ft_calloc(es_count(s, count) + 1, 1);
	while (s[i] != '\0')
	{
		if (s[i] == '\\')
		{
			str[j++] = s[i];
			if (s[i + 1] == '\\')
				i += 1;
		}
		else
			str[j++] = s[i];
		i += 1;
	}
	str[j] = '\0';
	free(s);
	return (str);
}
