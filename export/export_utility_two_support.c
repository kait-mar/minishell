/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utility_two_support.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molabhai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 13:47:13 by molabhai          #+#    #+#             */
/*   Updated: 2021/04/16 13:47:14 by molabhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*return_adding_quote(char *s, int j)
{
	char	*s2;
	int		i;

	s2 = ft_calloc(sizeof(char ), j + 3);
	if (!(s2))
		return (NULL);
	s2[0] = '\"';
	j = 1;
	i = 0;
	while (s[i] != '=')
		i += 1;
	if (s[i] == '=')
		i += 1;
	while (s[i] != '\0')
	{
		s2[j] = s[i];
		i += 1;
		j += 1;
	}
	s2[j] = '\"';
	j += 1;
	s2[j] = '\0';
	return (s2);
}

char	*return_loc(char *s, char *s2, char *str)
{
	int	i;
	int	j;

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

void	print_count(char *str, int *i, int *count)
{
	int	j;

	j = *i;
	while (((ft_isprint(str[j]) == 1 ) || str[j] == '=')
		&& ((check_single_double_quote(str[j]) == 0)
			|| (check_single_double_quote(str[j]) == 1
				&& j > 0 && str[j - 1] == '\\')))
		j += 1;
	*count += 1;
	*i = j;
}

void	double_quote_count(char *str, int *i, int *count)
{
	int	j;

	j = *i + 1;
	while (check_double_quotes(str[j]) == 0 && str[j] != '\0')
		j += 1;
	*count += 1;
	*i = j;
}

void	single_quote_count(char *str, int *i, int *count)
{
	int	j;

	j = *i + 1;
	while (check_single_quotes(str[j]) == 0 && str[j] != '\0')
		j += 1;
	*count += 1;
	*i = j;
}
