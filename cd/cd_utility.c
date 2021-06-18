/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utility.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molabhai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 19:01:30 by molabhai          #+#    #+#             */
/*   Updated: 2020/12/24 10:52:47 by molabhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*without_that(char *str, char c)
{
	int		i;
	int		j;
	char	*s;

	if (str == NULL)
		return (NULL);
	s = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (s == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c && str[i - 1] != '\\')
			i += 1;
		else if (str[i] == '\\' && str[i + 1] == '\"')
			i += 1;
		else
			s[j++] = str[i++];
	}
	s[j] = '\0';
	return (s);
}

int	how_mutch_arguments(char **str, int i)
{
	int	on;
	int	j;

	on = 0;
	while (str[i] != NULL)
	{
		j = 0;
		while (str[i][j] != '\0')
		{
			if (str[i][j])
				on = 1;
			j += 1;
		}
		i += 1;
	}
	return (on);
}

int	arguments_in(char **splits, int i)
{
	int	j;

	j = 0;
	while (splits[i] != NULL)
	{
		j += 1;
		i += 1;
	}	
	return (j);
}
