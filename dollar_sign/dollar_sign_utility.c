/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_sign_utility.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molabhai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 13:27:39 by molabhai          #+#    #+#             */
/*   Updated: 2021/03/29 13:27:42 by molabhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	escape_back_true(char *s, int i)
{
	int	count;

	count = 0;
	while (ft_isprint(s[i]))
		i += 1;
	if (s[i] == ' ')
		return (1);
	return (0);
}

char	*add_back_space(char *s)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	str = (char *) malloc(sizeof (char) * ft_strlen(s) + 2 );
	if (!str)
		return (NULL);
	while (s[i] != '\0')
		str[j++] = s[i++];
	str[j++] = ' ';
	str[j] = '\0';
	free(s);
	return (str);
}

char	*add_front_space(char *s)
{
	char	*string;
	int		len;
	int		i;
	int		j;

	i = 0;
	j = 0;
	len = ft_strlen(s) + 1;
	string = (char *) malloc(sizeof (char) * len + 1);
	if (!string)
		return (NULL);
	if (s[i] == '\\')
	{
		while (s[i] == '\\')
			s[j++] = s[i++];
	}
	string[j++] = ' ';
	while (s[i] != '\0')
		string[j++] = s[i++];
	string[j] = '\0';
	free(s);
	return (string);
}

int	check_inside_front_quote(char *s, int i)
{
	i -= 1;
	if (ft_isprint(s[i]))
	{
		while (ft_isprint(s[i]) && s[i] != '$' && s[i] != '"')
			i -= 1;
		if (s[i] == '$')
			return (1);
		else
			return (0);
	}
	return (1);
}

int	check_inside_back_quote(char *s, int i)
{
	i += 1;
	if (ft_isprint(s[i]))
	{
		while (ft_isprint(s[i]) && s[i] != '$' && s[i] != '"')
			i += 1;
		if (s[i] == '$')
			return (1);
		else
			return (0);
	}
	return (1);
}
