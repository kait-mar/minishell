/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kait-mar <kait-mar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 09:50:00 by kait-mar          #+#    #+#             */
/*   Updated: 2021/02/02 10:17:22 by kait-mar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//echo hello > $kait and kait is not in env !!!!!!!!!!!
t_meta	*redirect_intput(t_meta *meta, t_assen assen, char **env, int *status)
{
	int		fd;
	char	*new;
	t_meta	*temp;
	int		on;

	temp = meta;
	on = 0;
	while (temp->next != NULL && temp->meta == '<')
	{
		temp = temp->next;
		temp->argument = chang_dollar_sign(temp->argument, env);
		meta = input_conditions(meta, &new, temp, &on);
		fd = redirect_input_head(new);
		if ((fd) == -1)
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
		close(g_global.redirect_fd);
		close(fd);
	}
	else
		redirected_command(fd, meta, assen, env);
	return (temp);
}

t_meta	*input_conditions(t_meta *meta, char **new, t_meta *temp, int *on)
{
	char	*str;

	*new = file_name(temp->argument);
	str = temp->argument;
	temp->argument = ft_strdup(temp->argument + ft_strlen(*new));
	free(str);
	if ((temp->argument)[0] == ' ')
	{
		str = temp->argument;
		temp->argument = ft_strdup(temp->argument + 1);
		free(str);
	}
	str = take_first_word(temp->argument);
	if (meta->command == 0 && check_wich_command(str) != 0 && *on == 0)
	{
		free(str);
		meta = temp;
		str = take_first_word(temp->argument);
		//meta->command = check_wich_command(take_first_word(ft_strtrim(temp->argument, " ")));
		meta->command = check_wich_command(str);
		free(str);
		*on = 1;
	}
	else
		free(str);
	*new = final_file_name(*new);
	if (*on == 0)
	{
		if (ft_strcmp(meta->argument, "") != 0
			&& ft_strcmp(temp->argument, "") != 0
			&& (meta->argument[ft_strlen(meta->argument) - 1] != ' '
				&& *(temp->argument) != ' '))
		{
			str = meta->argument;
			meta->argument = ft_strjoin(meta->argument, " ");
			free(str);
		}
		str = meta->argument;
		meta->argument = ft_strjoin(meta->argument, temp->argument);
		free(str);
	}
	return (meta);
}
