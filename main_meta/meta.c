/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meta.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kait-mar <kait-mar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 15:33:43 by molabhai          #+#    #+#             */
/*   Updated: 2021/01/02 10:24:14 by kait-mar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_meta_struct(t_meta *meta)
{
	free(meta->argument);
	meta->argument = NULL;
	free(meta);
	meta = NULL;
}

int	valid(char *str, int j, int len)
{
	char	*s;
	int		i;

	s = from_to(str, j, len + 1);
	i = check_wich_command(str);
	if (i == 4)
	{
		while (j < len + 1)
		{
			if (check_single_double_quote(str[j]) == 1)
				return (1);
			j += 1;
		}
	}
	return (0);
}

int	count_meta(char *str)
{
	int	i;
	int	count;
	int	how_mutch;

	i = 0;
	how_mutch = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (skip_quote(str, &i))
			continue ;
		else if (str[i] == '\\')
			count = return_count_meta(str, &i, count, &how_mutch);
		else if (str[i] == '|' || str[i] == '<'
			|| str[i] == '>' || str[i] == ';')
		{
			count += 1;
			i += 1;
		}
		else
			i += 1;
	}
	return (count);
}

char	**splits_by_meta(char *str)
{
	int		i;
	int		j;
	int		k;
	char	**splits;

	i = 0;
	j = 0;
	k = 0;
	splits = (char **) ft_calloc(sizeof(char *), count_meta(str) + 2);
	while (ft_strcmp("", str) != 0 && str[i] != '\0')
	{
		if (skip_quote(str, &i))
			continue ;
		else if ((str[i] == ';' || str[i] == '|'
				|| str[i] == '<' || str[i] == '>') && (active(str, i) == 1))
			splits[k++] = filling_split(str, &i, &j);
		else
			i += 1;
	}
	splits[k++] = from_to(str, j, i);
	free(str);
	splits[k] = NULL;
	return (splits);
}
