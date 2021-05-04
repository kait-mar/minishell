/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_append.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molabhai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 11:13:33 by molabhai          #+#    #+#             */
/*   Updated: 2021/01/02 10:06:39 by molabhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_file(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && str[i] != ' ')
	{
		if (str[i] == '"')
		{
			i++;
			while (str[i] != '\0' && str[i] != '"')
				i++;
		}
		else if (str[i] == '\'')
		{
			i++;
			while (str[i] != '\0' && str[i] != '\'')
				i++;
		}
		i++;
	}
	return (i);
}

char	*file_name(char *str)
{
	char	*name;
	int		i;
	int		j;

	i = 0;
	j = count_file(str);
	name = ft_calloc(1, j + 1);
	j = 0;
	while (str[i] != '\0' && str[i] != ' ')
	{
		if (str[i] == '"')
		{
			name[j++] = str[i++];
			while (str[i] != '\0' && str[i] != '"')
				name[j++] = str[i++];
		}
		else if (str[i] == '\'')
		{
			name[j++] = str[i++];
			while (str[i] != '\0' && str[i] != '\'')
				name[j++] = str[i++];
		}
		name[j++] = str[i++];
	}
	return (name);
}
