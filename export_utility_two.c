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
