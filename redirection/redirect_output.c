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

t_meta	*redirect_output(t_meta *meta, t_assen assen, char **env, int *status)
{
	int			fd;
	t_support	support;
	t_meta		*temp;
	char		*new;
	t_meta		*tp;

	temp = meta;
	tp = temp;
	support.on = 0;
	while (temp->next != NULL && (temp->meta == '>' || temp->meta_append != 0))
	{
		support.on = 0;
		support.append = 0;
		support.check_meta = 0;
		if (temp->meta_append != 0)
			support.append = 1;
		else if (temp->meta == '>')
			support.check_meta = '>';
		temp = temp->next;
		//r emove chang_dolar_sign
		temp->argument = chang_dollar_sign(temp->argument, env);
		meta = name_and_condition(&new, &(support.on), meta, temp);
		fd = redirect_command_head(support.check_meta, support.append, new);
		free(new);
		if (fd == -1)
			return (NULL);
	}
	if (temp->meta == '|')
	{
		g_global.redirect = 1;
		g_global.redirect_fd = fd;
		pipe_file(meta, assen, env, status);
		while (temp->meta != '|')
			temp = temp->next;
		if (temp->next != NULL)
			temp = temp->next;
		redirected_output_command(fd, meta, assen, env);
		close(g_global.redirect_fd);
		close(fd);
	}
	else
		redirected_output_command(fd, meta, assen, env);
	return (temp);
}

char	*final_file_name(char *file)
{
	char	*new;
	char	*temp;
	int		i;
	int		len;
	char	**split;

	split = keep_split(file, 39, 34);
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
