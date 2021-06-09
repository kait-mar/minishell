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

#include "../minishell.h"

t_meta	*meta_for_in(char *s, t_meta *global)
{
	char	*arg_free;

	arg_free = s;
	s = remove_space(s);
	free(arg_free);
	s = escape_meta(s);
	arg_free = s;
	s = escape_normal(s);
	free(arg_free);
	if (global->command != 0 && global->command != 6)
	{
		global->argument = skip_first_word(s);
		arg_free = global->argument;
		global->argument = ft_strtrim(global->argument, "\t");
		free(arg_free);
	}
	else if (global->command == 0 || global->command == 6)
	{
		global->argument = ft_strdup(s);
		arg_free = global->argument;
		global->argument = ft_strtrim(global->argument, "\t");
		free(arg_free);
	}
	free(s);
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
	char	*split_free;

	global->meta = 0;
	if (ft_strcmp(splits[*i], "") == 0)
		global->argument = ft_strdup("");
	if (splits[*i] != NULL && ft_strcmp(splits[*i], "") != 0)
	{
		split_free = splits[*i];
		splits[*i] = remove_space(splits[*i]);
		free(split_free);
		splits[*i] = escape_meta(splits[*i]);
		if (global->command != 0 && global->command != 6)
		{
			global->argument = skip_first_word(splits[*i]);
			split_free = global->argument;
			global->argument = ft_strtrim(global->argument, "\t");
			free(split_free);
		}
		else if (global->command == 0 || global->command == 6)
			global->argument = ft_strdup(splits[*i]);
	}
	global->meta_append = 0;
	*i += 1;
	return (global);
}

t_meta	*meta_for_in_between(char *s, t_meta *temp)
{
	char	*temp_free;

	temp_free = s;
	s = remove_space(s);
	free(temp_free);
	s = escape_meta(s);
	temp_free = s;
	s = escape_normal(s);
	free(temp_free);
	if (temp->command != 0 && temp->command != 4 && temp->command != 6)
	{
		temp->argument = skip_first_word(s);
		temp_free = temp->argument;
		temp->argument = ft_strtrim(temp->argument, "\t");
		free(temp_free);
	}
	else if (temp->command == 0 || temp->command == 4 || temp->command == 6)
	{
		temp->argument = ft_strdup(s);
		temp_free = temp->argument;
		temp->argument = ft_strtrim(temp->argument, "\t");
		free(temp_free);
	}
	free(s);
	return (temp);
}

t_meta	*meta_in_between(char **splits, t_meta *temp, int *i)
{
	char	*s;

	s = NULL;
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
