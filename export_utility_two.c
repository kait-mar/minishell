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

#include "minishell.h"


int     check_equal(char *s)
{
    int i;

    i = 0;
    while (s[i] != '\0')
    {
        if (s[i] == '=')
            return (1);
        i += 1;
    }
    return (0);
}

char    *adding_quote(char *s)
{
    char *s1;
    char *s2;
    int i;
    int j;
    char *str;

    i = 0;
    j = 0;

   if (check_equal(s) == 0)
       return (ft_strdup(s));

    while (s[i] != '=')
        i += 1;
    if (!(s1 = (char *) ft_calloc(sizeof (char ), i + 1)))
        return (NULL);
    while (s[i] != '\0')
    {
        j += 1;
        i += 1;
    }
    if (!(s2 = (char *) ft_calloc(sizeof (char ), j + 3)))
        return (NULL);
    i = 0;
    while (s[i] != '=')
        i += 1;
    if (s[i] == '=')
        i += 1;
    if (!(str = (char *) ft_calloc(sizeof(char ), j + i + 1)))
        return (NULL);
    s2[0] = '\"';
    j = 1;
    while (s[i] != '\0')
    {
        s2[j] = s[i];
        i += 1;
        j += 1;
    }
    s2[j] = '\"';
    j += 1;
    s2[j] = '\0';
    i = 0;
    j = 0;
    while (s[i] != '=')
    {
        str[i] = s[i];
        i += 1;
    }
    str[i] = s[i];
    i += 1;
    while (s2[j] != '\0')
    {
        str[i] = s2[j];
        i += 1;
        j += 1;
    }
    str[i] = '\0';
    return (str);
}

char	*front_append(char *string, char *to_append)
{
	char *s;
	int i;
	int j;

	if (!(s = (char *) malloc(sizeof(char) * (ft_strlen(string) + ft_strlen(to_append) + 1))))
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

int		kait_count(char *str)
{
	int i;
	int	j;
	int k;
	int	count;

	i = 0;
	k = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (ft_isprint(str[i]))
		{
			j = i;
			while (((ft_isprint(str[j]) == 1 ) || str[j] == '=') &&
					(check_single_double_quote(str[j]) == 0))
				j += 1;
			count += 1;
			i = j;
		}
		if (check_double_quotes(str[i]))
		{
			j = i + 1;
			while (check_double_quotes(str[j]) == 0)
				j += 1;
			count += 1;
		   i = j;
		}
		if (check_single_quotes(str[i]))
		{
			j = i + 1;
			while (check_single_quotes(str[j]) == 0)
				j += 1;
			count += 1;
		   i = j;
		}
		if (str[i] != '\0')
			i += 1;
	}
	return (count);
}	

void    filling_export(char **env)
{
    int i;

    i = 0;
    if (!(g_export = (t_export *) malloc(sizeof (t_export))))
        return ;
    if (!(g_export->saver = (char **) ft_calloc(sizeof (char *), arguments_in(env, i) + 1)))
        return ;
    while (env[i])
    {
        g_export->saver[i] = ft_strdup(env[i]);
        i += 1;
    }
}