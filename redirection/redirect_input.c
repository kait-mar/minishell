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
	t_meta	*temp;
	int		on;
	int		j;

	temp = init_in(meta, &on, &j);
	while (temp->next != NULL && temp->meta == '<')
	{
		temp = red2(temp, env);
		meta = ret_in_meta(meta, temp, &on, &fd);
		if ((fd) == -1 && temp->meta != '|')
			return (NULL);
	}
	checking_out(temp, meta, env, &j);
	if (temp->meta == '|')
	{
		meta = red3(meta, fd);
		temp = redirect_pipe(meta, temp, env, assen);
		temp = pipe_in_loop(temp, fd);
	}
	else
		redirected_command(fd, meta, assen, env);
	temp = ret_temp_in(temp, assen, env, j);
	return (temp);
}

t_meta	*independent_func(t_meta *temp, t_meta *meta, char **env)
{
	t_support		support;
	char			*new;

	while (temp->next != NULL && (temp->meta == '>' || temp->meta_append != 0))
	{
		temp = return_value(&support, temp, env);
		if (temp == NULL)
			return (NULL);
		meta = name_and_condition(&new, &(support.on), meta, temp);
		g_global.check_fd = redirect_command_head
			(support.check_meta, support.append, new);
		free(new);
		if (g_global.check_fd == -1)
			return (NULL);
	}
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
