/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utility_support.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molabhai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 14:02:13 by molabhai          #+#    #+#             */
/*   Updated: 2021/04/15 14:02:15 by molabhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	last_check_first(char *str, int i)
{
	while (str[i] != '=')
	{
		if (str[i] == '\\' && (str[i + 1] == '\\'
				|| str[i + 1] == '\'' || str[i + 1] == '\"'
				|| str[i + 1] == '$' || str[i + 1] == '&'
				|| str[i + 1] == '|' || str[i + 1] == ';'))
			return (1);
		i++;
	}
	return (0);
}

int	last_check_second(char *str, int i)
{
	while (str[i] != '=')
	{
		if (str[i] == '\\' && (str[i + 1] == '\\'
				|| str[i + 1] == '\'' || str[i + 1] == '\"'
				|| str[i + 1] == '$' || str[i + 1] == '&'
				|| str[i + 1] == '|' || str[i + 1] == ';'))
			return (1);
		i++;
	}
	return (0);
}

int	last_check_third(char *str, int i)
{
	while (str[i] != '\0')
	{
		if (str[i] == '\\' && (str[i + 1] == '\\' || str[i + 1] == '\''
				|| str[i + 1] == '\"'
				|| str[i + 1] == '$' || str[i + 1] == '&'
				|| str[i + 1] == '|' || str[i + 1] == ';'))
			return (1);
		i++;
	}
	return (0);
}

void	match_free(char *env, char *new_argument)
{
	free(env);
	free(new_argument);
	env = NULL;
	new_argument = NULL;
}

int	take_only_return(char *str, int j)
{
	while (((ft_isprint_mod(str[j]) == 1) || str[j] == '=')
		|| (str[j] == ' ' && str[j - 1] == '\\'))
	{
		if (str[j] == '\"' && str[j - 1] != '\\')
		{
			j += 1;
			while (str[j] != '\"' && str[j] != '\0')
				j += 1;
		}
		else if (str[j] == '\'' && str[j - 1] != '\\')
		{
			j += 1;
			while (str[j] != '\'' && str[j] != '\0')
				j += 1;
		}
		j += 1;
	}
	return (j);
}
