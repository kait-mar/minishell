/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meta_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molabhai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 09:31:29 by molabhai          #+#    #+#             */
/*   Updated: 2021/04/10 09:31:31 by molabhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_meta	*meta_for_in(char *s, t_meta *global)
{
	s = remove_space(s);
	s = escape_meta(s);
	if (global->command != 0 && global->command != 6)
	{
		global->argument = skip_first_word(&s);
		global->argument = ft_strtrim(global->argument, "\t");
	}
	else if (global->command == 0 || global->command == 6)
	{
		global->argument = ft_strdup(s);
		global->argument = ft_strtrim(global->argument, "\t");
	}
	return (global);
}

t_meta	*meta_in(char **splits, t_meta *global, int *i)
{
	char	*s;

	if (check_append(splits[*i]) == TRUE)
	{
		s = ft_substr(splits[*i], 0, until_meta(splits[*i]));
		global->meta_append = 1;
	}
	else
	{
		global->meta_append = 0;
		s = ft_substr(splits[*i], 0, until_meta(splits[*i]));
	}
	global->meta = splits[*i][until_meta(splits[*i])];
	if (s != NULL)
		global = meta_for_in(s, global);
	*i += 1;
	return (global);
}

t_meta	*meta_out(char **splits, t_meta *global, int *i)
{
	global->meta = 0;
	if (splits[*i] != NULL)
	{
		splits[*i] = remove_space(splits[*i]);
		splits[*i] = escape_meta(splits[*i]);
		if (global->command != 0 && global->command != 6)
		{
			global->argument = skip_first_word(&splits[*i]);
			global->argument = ft_strtrim(global->argument, "\t");
		}
		else if (global->command == 0 || global->command == 6)
			global->argument = strdup(splits[*i]);
	}
	global->meta_append = 0;
	*i += 1;
	return (global);
}

t_meta	*meta_for_in_between(char *s, t_meta *temp)
{
	s = remove_space(s);
	s = escape_meta(s);
	if (temp->command != 0 && temp->command != 4 && temp->command != 6)
	{
		temp->argument = skip_first_word(&s);
		temp->argument = ft_strtrim(temp->argument, "\t");
	}
	else if (temp->command == 0 || temp->command == 4 || temp->command == 6)
	{
		temp->argument = ft_strdup(s);
		temp->argument = ft_strtrim(temp->argument, "\t");
	}
	return (temp);
}

t_meta	*meta_in_between(char **splits, t_meta *temp, int *i)
{
	char	*s;

	if (check_append(splits[*i]) == TRUE)
	{
		s = ft_substr(splits[*i], 0, until_meta(splits[*i]));
		temp->meta_append = 1;
	}
	else
	{
		temp->meta_append = 0;
		s = ft_substr(splits[*i], 0, until_meta(splits[*i]));
	}
	temp->meta = splits[*i][until_meta(splits[*i])];
	if (s != NULL)
		temp = meta_for_in_between(s, temp);
	return (temp);
}
