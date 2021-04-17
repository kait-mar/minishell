/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executable_support5.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molabhai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 15:41:24 by molabhai          #+#    #+#             */
/*   Updated: 2021/04/17 15:41:25 by molabhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	parsed_func2(char **bult, char **str, char **env)
{
	if (**bult == '\'')
	{
		*bult = ft_strtrim(*bult, "'");
		*str = ft_strjoin(*str, *bult);
	}
	else
	{
		*bult = ft_strtrim(*bult, "\"");
		print_env_two(*bult, env, 1, str);
	}
}

void	parsed_func3(char **bult, int *which_quote)
{
	if (**bult == 39)
	{
		*bult = trim_once(*bult);
		*which_quote = 39;
	}
	else if (**bult == 34)
	{
		*bult = trim_once(*bult);
		*which_quote = 34;
	}
}

char	*parsed_func4(char **bult, char *str)
{
	int		j;
	char	*t;

	t = malloc(2);
	j = how_many_escape(*bult);
	if (j % 2 != 0)
	{
		while (*(*bult + 1) == '\\')
			(*bult)++;
	}
	else
	{
		while (**bult == '\\')
			(*bult)++;
	}
	j /= 2;
	while (--j >= 0)
	{
		t[0] = '\\';
		t[1] = '\0';
		str = ft_strjoin(str, t);
	}
	return (str);
}

char	*parsed_func5(char **bult, char *str)
{
	char	*t;

	t = malloc(2);
	*t = **bult;
	t[1] = '\0';
	str = ft_strjoin(str, t);
	(*bult)++;
	return (str);
}

char	*parsed_func6(char **bult, char *str)
{
	char	*t;

	t = malloc(2);
	t[0] = **bult;
	t[1] = '\0';
	str = ft_strjoin(str, t);
	(*bult)++;
	return (str);
}
