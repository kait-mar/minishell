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
	*new = file_name(temp->argument);
	temp->argument = temp->argument + ft_strlen(*new);
	if (*(temp->argument) == ' ')
		(temp->argument)++;
	if (meta->command == 0
		&& check_wich_command(take_first_word(temp->argument)) != 0
		&& *on == 0)
	{
		meta = temp;
		meta->command = check_wich_command(
				take_first_word(ft_strtrim(temp->argument, " ")));
		*on = 1;
	}
	*new = final_file_name(*new);
	if (*on == 0)
	{
		if (ft_strcmp(meta->argument, "") != 0
			&& ft_strcmp(temp->argument, "") != 0
			&& (meta->argument[ft_strlen(meta->argument) - 1] != ' '
				&& *(temp->argument) != ' '))
			meta->argument = ft_strjoin(meta->argument, " ");
		meta->argument = ft_strjoin(meta->argument, temp->argument);
	}
	return (meta);
}
