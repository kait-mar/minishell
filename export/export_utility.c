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

#include "../minishell.h"

int	not_before(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\\' && (s[i + 1] == '_' || ft_isdigit(s[i + 1])))
			return (1);
		i += 1;
	}
	return (0);
}

int	last_check(char *str, int on)
{
	int	i;

	i = 0;
	if (on == 0)
	{
		if (last_check_first(str, i) == 1)
			return (1);
	}
	else if (on == 1)
	{
		if (check_exp_lex(str) == 1)
		{
			if (last_check_second(str, i) == 1)
				return (1);
		}
		else if (check_equal(str) == 1 && check_exp_lex(str) == 0
			&& not_before(str) == 0)
			return (1);
		else
		{
			if (last_check_third(str, i) == 1)
				return (1);
		}
	}
	return (0);
}

int	check_exp_lex(char *str)
{
	int	i;

	i = 0;
	if (ft_isalpha(str[i]) == 0 && str[i] != '_')
		return (0);
	while (ft_isalpha(str[i]) || str[i] == '_' || ft_isdigit(str[i]))
		i += 1;
	if (str[i] == '=')
	{
		if (last_check(str, 0) == 0)
			return (1);
	}
	return (0);
}

char	*take_before_equal(char *str)
{
	int		i;
	char	*s;

	i = 0;
	s = ft_calloc(sizeof(char), ft_strlen(str) + 1);
	if (!(s))
		return (NULL);
	while (str[i] != '=')
	{
		s[i] = str[i];
		i += 1;
	}
	s[i] = '\0';
	return (s);
}

int	match(char *str, char *export)
{
	char	*env;
	char	*new_argument;

	if (check_exp_lex(str) == 1)
		env = take_before_equal(str);
	else
		env = return_alloc_env(str);
	if (check_exp_lex(export) == 1)
		new_argument = take_before_equal(export);
	else
		new_argument = ft_strdup(export);
	if (ft_strlen(env) != ft_strlen(new_argument))
	{
		match_free(env, new_argument);
		return (0);
	}
	if (ft_strncmp(env, new_argument, ft_strlen(env)) == 0)
	{
		match_free(env, new_argument);
		return (1);
	}
	match_free(env, new_argument);
	return (0);
}
