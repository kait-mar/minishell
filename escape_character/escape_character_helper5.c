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
