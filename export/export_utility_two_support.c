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

	i = 0;
	s2 = (char *) ft_calloc(sizeof (char ), j + 3);
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
				   && str[j - 1] == '\\')))
		j += 1;
	*count += 1;
	*i = j;
}

void	double_quote_count(char *str, int *i, int *count)
{
	int	j;

	j = *i + 1;
	while (check_double_quotes(str[j]) == 0)
		j += 1;
	*count += 1;
	*i = j;
}

void	single_quote_count(char *str, int *i, int *count)
{
	int	j;

	j = *i + 1;
	while (check_single_quotes(str[j]) == 0)
		j += 1;
	*count += 1;
	*i = j;
}

/*remove_space_support(string, &i, &start, &end);
void	remove_space_support(char *string, int *i, int *start, int *end)
{
	while (string[*i] == ' ')
		*i += 1;
	*start = *i;
	*end = ft_strlen(string) - 1;
	while (string[*end] == ' ')
		(*end)--;
	if (string[*end] == '\\')
		*end += 1;
}




str = remove_space_quotes(str, string, &j, &start);
char	*remove_space_quotes(char *str, char *string, int *j, int *start)
{
	if (string[*start] == '"')
	{
		str[(*j)++] = string[(*start)++];
		while (string[(*start)] != '\0' && string[(*start)] != '"')
		{
			str[(*j)] = string[*start];
			*j += 1;
			*start += 1;
		}
		str[(*j)++] = string[(*start)++];
	}
	else if (string[*start] == '\'')
	{
		str[(*j)++] = string[(*start)++];
		while (string[*start] != '\0' && string[*start] != '\'')
		{
			str[(*j)] = string[*start];
			*j += 1;
			start += 1;
		}
		str[(*j)++] = string[(*start)++];
	}
	return 
}*/