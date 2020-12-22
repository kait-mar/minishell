/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utility.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molabhai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 11:56:12 by molabhai          #+#    #+#             */
/*   Updated: 2020/12/21 13:04:48 by molabhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int		check_exp_lex(char *str)
{
	int i;

	i = 0;
	if (ft_isalpha(str[i]) == 0)
		return (0);
	while (ft_isalpha(str[i]))
		i += 1;
	if (str[i] == '=')
		return (1);
	return (0);
}

static char		*take_before_equal(char *str)
{
	int i;
	char *s;

	i = 0;
	if (!(s = (char *) malloc(sizeof(char) * ft_strlen(str) + 1)))
		return (NULL);
	while (str[i] != '=')
	{
		s[i] = str[i];
		i += 1;
	}
	s[i] = '\0';
	return (s);
}

int		match(char *str, char  *export)
{
	char *env;
	char *new_argument;

	env = take_before_equal(str);
	new_argument = take_before_equal(export);
	if (ft_strlen(env) != ft_strlen(new_argument))
	{
		free(env);
		free(new_argument);
		env = NULL;
		new_argument = NULL;
		return (0);
	}
	if (ft_strncmp(env, new_argument, ft_strlen(env)) == 0)
	{
		free(env);
		free(new_argument);
		env = NULL;
		new_argument = NULL;
		return (1);
	}
	return (0);
}

int		check_single_double_quote(char c)
{
	if (c == '\"' || c == '\'')
		return (1);
	return (0);
}

int		check_single_quotes(char c)
{
	if (c == '\'')
		return (1);
	return (0);
}

int		check_double_quotes(char c)
{
	if (c == '\"')
		return (1);
	return (0);
}

char	*from_to(char *str, int i, int j)
{
	char *s;
	int k;

	if (!(s = (char *) malloc(sizeof(char) * (j - i) + 1)))
		return (NULL);
	k = 0;
	while (i < j)
	{
		s[k] = str[i];
		k += 1;
		i += 1;
	}
	s[k] = '\0';
	return (s);
}

char	**take_only_carac(char *str)
{
	int i;
	char **splits;
	int	j;
	int k;

	i = 0;
	if (!(splits = (char **) ft_calloc(sizeof(char *) , kait_count(str) + 1)))
		return (NULL);
	k = 0;
	while (str[i] != '\0')
	{
		if (ft_isprint(str[i]))
		{
			j = i;
			while (((ft_isprint(str[j]) == 1 ) || str[j] == '=') &&
					(check_single_double_quote(str[j]) == 0))
				j += 1;
			splits[k++] = from_to(str, i, j);
			i = j;
		}
		if (check_double_quotes(str[i]))
		{
			j = i + 1;
			while (check_double_quotes(str[j]) == 0)
				j += 1;
			splits[k++] = from_to(str, i, j + 1);
		   i = j;	
		}
		if (check_single_quotes(str[i]))
		{
			j = i + 1;
			while (check_single_quotes(str[j]) == 0)
				j += 1;
			splits[k++] = from_to(str, i, j + 1);
		   i = j;	
		}
		if (str[i] != '\0')
			i += 1;
	}
	splits[k++] = NULL;
	return (splits);
}

void	free_splits(char **splits)
{
	int i;

	i = 0;
	while (splits[i] != NULL)
	{
		free(splits[i]);
		i += 1;
	}
	free(splits);
}
