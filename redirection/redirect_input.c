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

t_meta	*redirect_intput(t_meta *meta, t_assen assen, char **env)
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
		g_global.redirect_fd = fd;
		temp = redirect_pipe(meta, temp, env, assen);
		close(fd);
	}
	else
		redirected_command(fd, meta, assen, env);
	return (temp);
}

t_meta	*redirect_pipe(t_meta *meta, t_meta *temp, char **env, t_assen assen)
{
	g_global.redirect = 1;
	pipe_file(meta, assen, env);
	while (temp->meta == '|')
		temp = temp->next;
	while (temp->meta == '>')
		temp = temp->next;
	close(g_global.redirect_fd);
	return (temp);
}

int	input_conditions1(t_meta *meta, t_meta *temp)
{
	return (ft_strcmp(meta->argument, "") != 0
		&& ft_strcmp(temp->argument, "") != 0
		&& (meta->argument[ft_strlen(meta->argument) - 1] != ' '
			&& *(temp->argument) != ' '));
}

t_meta	*meta_input(t_meta *meta, t_meta *temp, int *on)
{
	char	*str;

	str = take_first_word(temp->argument);
	if (meta->command == 0 && check_wich_command(str) != 0 && *on == 0)
	{
		free(str);
		meta = temp;
		str = take_first_word(temp->argument);
		meta->command = check_wich_command(str);
		*on = 1;
	}
	free(str);
	return (meta);
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
	meta = meta_input(meta, temp, on);
	*new = final_file_name(*new);
	if (*on == 0)
	{
		if (input_conditions1(meta, temp))
			meta = input_free(meta);
		str = meta->argument;
		meta->argument = ft_strjoin(meta->argument, temp->argument);
		free(str);
	}
	return (meta);
}
