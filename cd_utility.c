/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utility.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molabhai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 19:01:30 by molabhai          #+#    #+#             */
/*   Updated: 2020/12/10 13:51:26 by molabhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*without_that(char *str, char c)
{
	int i;
	int j;
	char *s;

	if (str == NULL)
		return (NULL);
	s = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (s == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			i += 1;
		else
		{
			s[j] = str[i];
			j += 1;
			i += 1;
		}
	}
	s[j] = '\0';
	return (s);
}

int		how_mutch_argument(char *str, int i)
{
	int on;

	on = 0;
	while (str[i] != '\0')
	{
		if (ft_isalpha(str[i]) || (str[i] == '.'))
			on = 1;
		i += 1;
	}
	if (on == 1)
		return (1);
	return (0);
}

int		how_mutch_arguments(char **str, int i)
{
	int on;
	int	j;

	on = 0;
	while (str[i] != NULL)
	{
		j = 0;
		while (str[i][j] != '\0')
		{
			if (ft_isalpha(str[i][j]) == 0)
				on = 1;
			j += 1;
		}
		i += 1;
	}
	return (on);
}

int		arguments_in(char **splits, int i)
{
	int j;

	j = 0;
	while (splits[i] != NULL)
	{
		j += 1;
		i += 1;
	}	
	return (j);
}

void	free_export(t_export *export)
{
	int i;

	i = 0;
	while (export->argument[i])
	{
		free(export->argument[i]);
		i +=  1;
	}
	free(export->argument);
	free(export->command);
	free(export);
}
