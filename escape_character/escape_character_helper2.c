/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escape_character_helper2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kait-mar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 14:07:28 by kait-mar          #+#    #+#             */
/*   Updated: 2021/04/17 14:07:30 by kait-mar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	new_space(char *str)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '"')
			count = new_space_dquote(str, count, &i);
		else if (str[i] == '\\')
		{
			if (check_escape_meta(str, i) == 1)
				count = new_space_quote(str, count, &i);
			else
				count = new_space_core(str, count, &i);
		}
		else
		{
			i += 1;
			count += 1;
		}
	}
	return (count);
}

int	new_space_dquote(char *str, int count, int *i)
{
	*i += 1;
	count += 1;
	while (str[*i] != '"' && str[*i] != '\0')
	{
		*i += 1;
		count += 1;
	}
	if (str[*i] == '"')
	{
		*i += 1;
		count += 1;
	}
	return (count);
}

int	new_space_quote(char *str, int count, int *i)
{
	while (str[*i] != '|' && str[*i] != '<' && str[*i] != '>' && str[*i] != ';')
	{
		*i += 1;
		count += 1;
	}
	if (str[*i] == '|' || str[*i] == '<' || str[*i] == '>' || str[*i] == ';')
	{
		*i += 1;
		count += 1;
	}
	return (count);
}

int	new_space_core(char *str, int count, int *i)
{
	int	escape_nmbr;

	if (check_escape_dollar(str, *i) == 1)
	{
		while (str[*i] != '$')
			increment(&count, i);
		if (str[*i] == '$')
			increment(&count, i);
	}
	else
	{
		escape_nmbr = count_escape(str, *i);
		escape_nmbr = escape_nmbr % 2;
		while (str[*i] == '\\')
			*i += 1;
		count += escape_nmbr;
		if (str[*i] != '\\')
			*i += 1;
		count++;
	}
	return (count);
}

void	increment(int *count, int *i)
{
	*i += 1;
	*count += 1;
}
