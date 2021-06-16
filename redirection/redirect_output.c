/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_output.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kait-mar <kait-mar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 10:07:34 by kait-mar          #+#    #+#             */
/*   Updated: 2021/01/05 09:49:24 by kait-mar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_meta	*redirect_output(t_meta *meta, t_assen assen, char **env)
{
	t_redirection	red;
	t_support		support;
	t_meta			*temp;
	t_meta			*check;
	char			*new;

	support = output_initializer(&temp, &check, meta);
	while (temp->next != NULL && (temp->meta == '>' || temp->meta_append != 0))
	{
		temp = return_value(&support, temp, env);
		if (temp == NULL)
			return (NULL);
		meta = name_and_condition(&new, &(support.on), meta, temp);
		red.fd = redirect_command_head(support.check_meta, support.append, new);
		free(new);
		if (red.fd == -1)
			return (NULL);
	}
	temp = redirect_temp(temp, assen, env, check);
	if (check != NULL)
		redirected_output_command(red.fd, meta, assen, env);
	red.assen = assen;
	temp = global_temp(temp, red, env, meta);
	return (temp);
}

t_meta	*redirect_temp(t_meta *temp, t_assen assen, char **env, t_meta *check)
{
	if (temp->meta == '<')
		check = redirect_intput(temp, assen, env);
	if (check == NULL)
	{
		while (temp != NULL && temp->meta == '<')
			temp = temp->next;
		while (temp != NULL && (temp->meta == '>' || temp->meta_append == 0))
			temp = temp->next;
	}
	return (temp);
}

t_meta	*global_temp(t_meta *temp, t_redirection red, char **env, t_meta *meta)
{
	if (temp->meta == '|')
	{
		g_global.redirect = 1;
		g_global.redirect_fd = red.fd;
		while (meta->meta == '>' && meta->next != NULL)
			meta = meta->next;
		temp = pipe_file(meta, red.assen, env);
	}
	close(red.fd);
	return (temp);
}

char	*final_file_name(char *file)
{
	char	*new;
	char	*temp;
	int		i;
	char	**split;

	if (g_global.only_in_space == 1)
	{
		new = ft_strdup(file);
		free(file);
		g_global.only_in_space = 0;
		return (new);
	}
	split = keep_split(file, 39, 34);
	split = fill_split(split);
	i = 1;
	new = ft_strdup(split[0]);
	while (split[i])
	{
		temp = new;
		new = ft_strjoin(new, split[i++]);
		free(temp);
	}
	free(file);
	to_free(split);
	return (new);
}

char	**fill_split(char **split)
{
	int		i;
	char	*temp;

	i = 0;
	while (split[i] != NULL)
	{
		if (*(split[i]) == '\'')
		{
			temp = split[i];
			split[i] = ft_strtrim(split[i], "'");
			free(temp);
		}
		else if (*(split[i]) == '"')
		{
			temp = split[i];
			split[i] = ft_strtrim(split[i], "\"");
			free(temp);
		}
		i++;
	}
	return (split);
}
