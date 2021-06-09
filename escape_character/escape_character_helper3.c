/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escape_character_helper3.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kait-mar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 15:28:48 by kait-mar          #+#    #+#             */
/*   Updated: 2021/04/17 15:28:50 by kait-mar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	in_quote(char *str, int i)
{
	int	j;

	j = i;
	while (str[j] == '\\')
		j += 1;
	if (str[j] == '\'' || str[j] == '"')
		return (1);
	return (0);
}

char	*escape_normal(char *str)
{
	int		i;
	int		j;
	char	*string;

	i = 0;
	j = 0;
	string = (char *) ft_calloc(sizeof(char), (new_space(str) + 1));
	if (string == NULL)
		return (NULL);
	while (str[i] != '\0')
	{
		escape_normal_head(str, &string, &i, &j);
	}
	string[j] = '\0';
	return (string);
}

void	escape_normal_core(char *str, char **string, int *i, int *j)
{
	if (check_escape_dollar(str, *i) == 1)
	{
		while (str[*i] != '$')
			(*string)[(*j)++] = str[(*i)++];
		if (str[*i] == '$')
			(*string)[(*j)++] = str[(*i)++];
		if (str[*i] == '\\')
		{
			while (str[*i] == '\\')
				(*string)[(*j)++] = str[(*i)++];
		}
	}
	else if (check_escape_space(str, *i) == 1)
	{
		while (str[*i] != ' ')
			(*string)[(*j)++] = str[(*i)++];
		if (str[*i] == ' ')
			(*string)[(*j)++] = str[(*i)++];
	}
	else
		escape_core_support(str, string, i, j);
}

void	escape_normal_dquote(char *str, char **string, int *i, int *j)
{
	(*string)[(*j)++] = str[(*i)++];
	while (str[*i] != '"' && str[*i] != '\0')
		(*string)[(*j)++] = str[(*i)++];
	if (str[*i] == '"')
		(*string)[(*j)++] = str[(*i)++];
}

void	escape_normal_head(char *str, char **string, int *i, int *j)
{
	if (str[*i] == '"')
		escape_normal_dquote(str, string, i, j);
	else if (str[*i] == '\\')
	{
		if (check_escape_meta(str, *i) == 1)
		{
			while (str[*i] != '|' && str[*i] != '<'
				&& str[*i] != '>' && str[*i] != ';')
				(*string)[(*j)++] = str[(*i)++];
			if (str[*i] == '|' || str[*i] == '<'
				|| str[*i] == '>' || str[*i] == ';')
				(*string)[(*j)++] = str[(*i)++];
		}
		else
			escape_normal_core(str, string, i, j);
	}
	else if (str[*i] == '$' && str[*i + 1] == '\\')
	{
		(*string)[(*j)++] = str[(*i)++];
		while (str[*i] == '\\')
			(*string)[(*j)++] = str[(*i)++];
	}
	else
		(*string)[(*j)++] = str[(*i)++];
}
