/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utility_two.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molabhai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 18:01:31 by molabhai          #+#    #+#             */
/*   Updated: 2020/12/12 18:47:00 by molabhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_equal(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '=')
			return (1);
		i += 1;
	}
	return (0);
}

char	*adding_quote(char *s)
{
	char	*s1;
	char	*s2;
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	if (check_equal(s) == 0)
		return (ft_strdup(s));
	while (s[i] != '=')
		i += 1;
	while (s[i] != '\0')
	{
		j += 1;
		i += 1;
	}
	str = (char *) ft_calloc(sizeof(char ), j + i + 1);
	if (!(str))
		return (NULL);
	s2 = return_adding_quote(s, j);
	str = return_loc(s, s2, str);
	return (str);
}

char	*front_append(char *string, char *to_append)
{
	char	*s;
	int		i;
	int		j;

	s = (char *) malloc(sizeof(char)
			* (ft_strlen(string) + ft_strlen(to_append) + 1));
	if (!(s))
		return (NULL);
	i = 0;
	while (to_append[i] != '\0')
	{
		s[i] = to_append[i];
		i += 1;
	}
	j = 0;
	while (string[j] != '\0')
	{
		s[i] = string[j];
		i += 1;
		j += 1;
	}
	s[i] = '\0';
	s = adding_quote(s);
	return (s);
}

int	kait_count(char *str)
{
	int	i;
	int	j;
	int	k;
	int	count;

	i = 0;
	k = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (ft_isprint(str[i]))
			print_count(str, &i, &count);
		if (check_double_quotes(str[i]) && str[i - 1] != '\\')
			double_quote_count(str, &i, &count);
		if (check_single_quotes(str[i]) && str[i - 1] != '\\')
			single_quote_count(str, &i, &count);
		if (str[i] != '\0')
			i += 1;
	}
	return (count);
}

char	*append(char *s1, char *s2)
{
	char	*str;
	int		len;
	int		i;
	int		j;

	i = 0;
	j = 0;
	len = ft_strlen(s1) + ft_strlen(s2);
	str = (char *) ft_calloc(sizeof (char ), len + 1);
	if (!(str))
		return (NULL);
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i += 1;
	}
	while (s2[j] != '\0')
	{
		str[i] = s2[j];
		i += 1;
		j += 1;
	}
	str[i] = '\0';
	return (str);
}
