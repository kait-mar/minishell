/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utility5.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kait-mar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 15:39:52 by kait-mar          #+#    #+#             */
/*   Updated: 2021/04/16 15:39:55 by kait-mar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*take_only_helper(char *s, int i)
{
	char	*string;

	string = (char *)ft_calloc(sizeof (char ), i + 2);
	if (string == NULL)
		return (NULL);
	i = 0;
	while (i < 2)
	{
		string[i] = s[i];
		i += 1;
	}
	string[i] = '\0';
	return (string);
}

char	*take_only_helper2(char *s, int i, char ref)
{
	char	*string;
	int		j;

	j = i;
	while (s[i] != ref && s[i] != '\0')
		i += 1;
	string = (char *) ft_calloc(sizeof (char ), i + 2);
	if (string == NULL)
		return (NULL);
	i = 0;
	string[i] = s[j++];
	i += 1;
	while (s[j] != ref && s[j] != '\0')
	{
		string[i] = s[j++];
		i += 1;
	}
	string[i] = '\0';
	return (string);
}

char	*take_only_helper3(char *s)
{
	int		i;
	char	*string;

	i = 0;
	while (s[i] != ' ' && s[i] != '\t' && s[i] != '\0')
		i += 1;
	string = (char *) ft_calloc(sizeof (char ), i + 1);
	if (!string)
		return (NULL);
	i = 0;
	while (s[i] != ' ' && s[i] != '\t' && s[i] != '\0')
	{
		string[i] = s[i];
		i += 1;
	}
	string[i] = '\0';
	return (string);
}

char	*take_only_core(char *s, int i)
{
	char	*string;

	if (s[i] == '\"')
	{
		string = take_only_helper(s, i);
		if (string == NULL)
			return (NULL);
	}
	else
	{
		string = take_only_helper2(s, i, '"');
		if (string == NULL)
			return (NULL);
	}
	return (string);
}
