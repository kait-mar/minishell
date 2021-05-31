/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escape_character_helper4.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kait-mar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 15:57:02 by kait-mar          #+#    #+#             */
/*   Updated: 2021/04/17 15:57:04 by kait-mar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_meta_space(char *str)
{
	int	i;
	int	nbr;
	int	count;

	i = 0;
	count = 0;
	nbr = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '"')
			count = new_space_dquote(str, count, &i);
		else if (str[i] == '\'')
			count = count_meta_quote(str, count, &i);
		else if (str[i] == '\\')
			count = count_with_mod(str, count, &i, &nbr);
		else
		{
			i += 1;
			count += 1;
		}
	}
	return (count);
}

int	count_meta_quote(char *str, int count, int *i)
{
	*i += 1;
	count += 1;
	while (str[*i] != '\'' && str[*i] != '\0')
	{
		*i += 1;
		count += 1;
	}
	if (str[*i] == '\'')
	{
		*i += 1;
		count += 1;
	}
	return (count);
}

int	count_with_mod(char *str, int count, int *i, int *nbr)
{
	if (check_escape_meta(str, *i) == 1)
	{
		while (str[*i] == '\\')
		{
			*i += 1;
			*nbr += 1;
		}
		count += *nbr % 2;
		if (str[*i] == '|' || str[*i] == '<'
			|| str[*i] == '>' || str[*i] == ';')
			*i += 1;
	}
	else
	{
		*i += 1;
		count += 1;
	}
	return (count);
}

void	escape_meta_head(char *str, char **string, int *i, int *j)
{
	if (str[*i] == '"')
	{
		(*string)[(*j)++] = str[(*i)++];
		while (str[*i] != '"' && str[(*i)] != '\0')
			(*string)[(*j)++] = str[(*i)++];
		if (str[*i] == '"')
			(*string)[(*j)++] = str[(*i)++];
	}
	if (str[*i] == '\'')
	{
		(*string)[(*j)++] = str[(*i)++];
		while (str[*i] != '\'' && str[*i] != '\0')
			(*string)[(*j)++] = str[(*i)++];
		if (str[*i] == '\'')
			(*string)[(*j)++] = str[(*i)++];
	}
}

void	escape_meta_core(char *str, char **string, int *i, int *j)
{
	if (check_escape_meta(str, *i) == 1 || check_escape_space(str, *i) == 1)
	{
		while ((str[*i] != '|' && str[*i] != '>'
				&& str[*i] != '<' && str[*i] != ';'
				&& str[*i] != '\0' && str[*i] != ' ') && str[*i] == '\\')
		{
			*i += 1;
			(*string)[(*j)++] = str[(*i)++];
		}
	}
	else
		(*string)[(*j)++] = str[(*i)++];
}
