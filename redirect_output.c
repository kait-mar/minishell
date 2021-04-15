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

#include "minishell.h"

t_meta	*redirect_output(t_meta *meta, t_assen assen, char **env, int *status)
{
	int		fd;
	t_support	support;
	t_meta	*temp;
	char	*new;

	temp = meta;
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
		temp->argument = chang_dollar_sign(temp->argument, env);
        meta = name_and_condition(&new, &(support.on), meta, temp);
		if ((fd = redirect_command_head(support.check_meta, support.append, new)) == -1)
			return (NULL);
	}
	redirected_output_command(fd, meta, assen, env);
	return (temp);
}

char	*final_file_name(char *file)
{
	char	*new;
	int		i;
	int		len;
	char	**split;

	split = keep_split(file, 39, 34);
	i = 0;
	while (split[i] != NULL)
	{
		if (*(split[i]) == '\'')
			split[i] = ft_strtrim(split[i], "'");
		else if (*(split[i]) == '"')
			split[i] = ft_strtrim(split[i], "\"");
		i++;
	}
	i = 1;
	new = ft_strdup(split[0]);
	while (split[i])
		new = ft_strjoin(new, split[i++]);
	return (new);
}
