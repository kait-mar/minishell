/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meta2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kait-mar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 18:52:22 by kait-mar          #+#    #+#             */
/*   Updated: 2021/05/27 18:52:24 by kait-mar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_append(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '>' && s[i + 1] == '>')
			return (TRUE);
		i += 1;
	}
	return (FALSE);
}

t_meta	*split_it_all(char *str, t_meta *global)
{
	char	**splits;
	int		i;
	int		check;
	char	*s;

	i = 0;
	check = 0;
	splits = NULL;
	global = (t_meta *) malloc(sizeof(t_meta));
	if (!global)
		return (NULL);
	splits = splits_by_meta(str);
	if (splits == NULL || splits[i] == NULL)
		return (NULL);
	s = take_first_word(splits[i]);
	global->command = check_wich_command(s);
	free(s);
	global = split_it_all_loop(splits, global, i);
	free_export_command(splits);
	return (global);
}

int	until_meta(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '"')
		{
			i = d_quotes(str, i, '"');
		}
		if (str[i] == '\'')
		{
			i = d_quotes(str, i, '\'');
		}
		if ((str[i] == '|' || str[i] == '>'
				|| str[i] == '<' || str[i] == ';') && active(str, i) == 1)
			return (i);
		i += 1;
	}
	return (i);
}

int	d_quotes(char *str, int i, char c)
{
	i += 1;
	while (str[i] != '\0' && str[i] != c)
		i += 1;
	if (str[i] == c)
		i += 1;
	return (i);
}
