/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meta_support_two.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molabhai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 10:56:05 by molabhai          #+#    #+#             */
/*   Updated: 2021/04/10 10:56:07 by molabhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	return_count_meta(char *str, int *i, int count, int *how_mutch)
{
	if (check_escape_meta(str, *i) == 1)
	{
		while (str[*i] != '|' && str[*i] != '<' && str[*i] != '>'
			&& str[*i] != ';')
		{
			*i += 1;
			*how_mutch += 1;
		}
		if (str[*i] == '|' || str[*i] == '<' || str[*i] == '>'
			|| str[*i] == ';')
			*i += 1;
		if ((*how_mutch % 2) == 0)
			count += 1;
	}
	else
		*i += 1;
	return (count);
}

t_meta 	*meta_out_between(char **splits, t_meta *temp, int *i)
{
	char	*temp_free;

	temp->meta = 0;
	if (splits[*i] != NULL)
	{
		temp_free = splits[*i];
		splits[*i] = remove_space(splits[*i]);
		free(temp_free);
		splits[*i] = escape_meta(splits[*i]);
		if (temp->command != 0 && temp->command != 4 && temp->command != 6)
		{
			temp = meta_out_between_core(temp, splits[*i]);
		}
		else if (temp->command == 0 || temp->command == 4 || temp->command == 6)
		{
			temp->argument = ft_strdup(splits[*i]);
			temp_free = temp->argument;
			temp->argument = ft_strtrim(temp->argument, "\t");
			free(temp_free);
		}
	}
	temp->meta_append = 0;
	return (temp);
}

t_meta 	*meta_out_between_core(t_meta *temp, char *splits)
{
	char	*temp_free;

	temp->argument = skip_first_word(splits);
	temp_free = temp->argument;
	temp->argument = ft_strtrim(temp->argument, "\t");
	free(temp_free);
	return (temp);
}
