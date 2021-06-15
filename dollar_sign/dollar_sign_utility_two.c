/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_sign_utility_two.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kait-mar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 17:37:15 by kait-mar          #+#    #+#             */
/*   Updated: 2021/04/14 17:37:17 by kait-mar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*rm_space_helper(int *i, char *s, int *j, int wich)
{
	char	*str;

	*i = 0;
	*j = 0;
	str = (char *) malloc(sizeof (char) * count_space_variable(s) + 1);
	if (!str)
		return (NULL);
	if (s[*i] == ' ')
	{
		if (wich == 1 || wich == 0)
		{
			str[*j] = s[*i];
			*i += 1;
			*j += 1;
		}
		while (s[*i] == ' ')
			*i += 1;
	}
	return (str);
}

int	return_loop(int i, char *s)
{
	while (s[i] == ' ')
		i += 1;
	return (i);
}

char	*rm_space_variable(char *s, int wich)
{
	int		i;
	int		j;
	char	*str;

	str = rm_space_helper(&i, s, &j, wich);
	if (str == NULL)
		return (NULL);
	while (s[i] != '\0' && ft_isprint(s[i]))
	{
		str[j++] = s[i++];
		if (s[i] == ' ' && only_space(s, i) == 0)
		{
			str[j++] = s[i++];
			i = return_loop(i, s);
		}
		else if (s[i] == ' ' && only_space(s, i) == 1)
		{
			if (wich == 2 || wich == 0)
				str[j++] = s[i++];
			i = return_loop(i, s);
			break ;
		}
	}
	str[j] = '\0';
	return (str_free(str, s));
}

int	inside_quotes(char *s, int i)
{
	int	count;

	count = 0;
	while (i > 0)
	{
		if (s[i] == '"')
			count += 1;
		i -= 1;
	}
	if ((count % 2) == 0)
		return (1);
	return (0);
}

int	escape_front_true(char *s, int i)
{
	int	count;

	count = 0;
	i = i - 1;
	while (i > 0 && s[i] == ' ')
	{
		i -= 1;
		count += 1;
	}
	if (count > 1)
		return (1);
	return (0);
}
