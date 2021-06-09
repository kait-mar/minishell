/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escape_character.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kait-mar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 14:07:18 by kait-mar          #+#    #+#             */
/*   Updated: 2021/04/17 14:07:20 by kait-mar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*escape_meta(char *str)
{
	int		i;
	int		j;
	char	*string;

	i = 0;
	j = 0;
	string = (char *) ft_calloc(sizeof(char), (count_meta_space(str) + 1));
	if (string == NULL)
		return (NULL);
	while (str[i] != '\0')
	{
		if (str[i] == '"' || str[i] == '\'')
			escape_meta_head(str, &string, &i, &j);
		else if (str[i] == '\\')
			escape_meta_core(str, &string, &i, &j);
		else
			string[j++] = str[i++];
	}
	string[j] = '\0';
	free(str);
	return (string);
}

int	count_dollar_escape(char *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\\' && check_escape_dollar(s, i) == 1)
			count = count_dollar_core(s, count, &i);
		else
		{
			i += 1;
			count += 1;
		}
	}
	return (count);
}

void	remove_escape_loop(char **str, char *s, int *i, int *j)
{
	while (s[*i] == '\\')
	{
		*i += 1;
		(*str)[(*j)++] = s[(*i)++];
	}
	(*str)[(*j)++] = s[(*i)++];
}

char	*remove_escape_dollar(char *s)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	str = malloc((sizeof (char) * count_dollar_escape(s) + 1));
	if (str == NULL)
		return (NULL);
	while (s[i] != '\0')
	{
		if (s[i] == '\\' && check_escape_dollar(s, i) == 1)
			remove_escape_loop(&str, s, &i, &j);
		else if (s[i] == '$' && s[i + 1] == '\\')
			remove_escape_dollar_support(&str, s, &i, &j);
		else
			str[j++] = s[i++];
	}
	str[j] = '\0';
	free(s);
	return (str);
}
