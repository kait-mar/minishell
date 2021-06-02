/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_sign3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kait-mar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 15:05:23 by kait-mar          #+#    #+#             */
/*   Updated: 2021/04/15 15:05:27 by kait-mar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_space_variable(char *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (s[i] == ' ')
	{
		count += 1;
		while (s[i] == ' ')
			i += 1;
	}
	while (ft_isprint(s[i]) && s[i] != '\0')
	{
		i += 1;
		count += 1;
		if (s[i] == ' ' && active(s, i) == 1)
		{
			count += 1;
			while (s[i] == ' ')
				i += 1;
		}
	}
	return (count);
}

int	only_space(char *s, int i)
{
	while (s[i] == ' ')
		i += 1;
	if (s[i] != '\0')
		return (0);
	return (1);
}

char	*take_after_equal(char *s)
{
	int		i;
	int		j;
	int		k;
	char	*string;

	i = 0;
	j = 0;
	take_after_equal_support(s, &i, &k, &j);
	string = (char *) ft_calloc(sizeof (char), j + 1);
	if (string == NULL)
		return (NULL);
	i = 0;
	while (s[k] != '\0')
		string[i++] = s[k++];
	string[i] = '\0';
	return (string);
}

void	take_after_equal_support(char *s, int *i, int *k, int *j)
{
	int	one_time;
	int	on;

	one_time = 0;
	on = 0;
	while (s[*i] != '\0')
	{
		if (s[*i] == '=' && one_time == 0)
		{
			on = 1;
			*k = *i + 1;
			one_time = 1;
		}
		if (on == 1)
			*j += 1;
		*i += 1;
	}
}
