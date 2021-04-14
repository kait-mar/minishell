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
	int     i;
	int		pid;
	char    **split;
	t_meta	*temp;
	char	*new;
    int     on;
    int     count;
	int		append;
	int		check_meta;

	temp = meta;
	i = 1;
    on = 0;
    count = 0;
	while (temp->next != NULL && (temp->meta == '>' || temp->meta_append != 0))
	{
		on = 0;
		append = 0;
		check_meta = 0;
		if (temp->meta_append != 0)
			append = 1;
		else if (temp->meta == '>')
			check_meta = '>';
		temp = temp->next;
		temp->argument = chang_dollar_sign(temp->argument, env);
		new = file_name(temp->argument);
        temp->argument = temp->argument + ft_strlen(new);
		if (*(temp->argument) == ' ')
			(temp->argument)++;
          if (meta->command == 0 && check_wich_command(take_first_word(temp->argument)) != 0 && on == 0)
        {
            meta = temp;
            meta->command = check_wich_command(take_first_word(temp->argument));
            on = 1;
        }
        new = final_file_name(new);
        if (on == 0)
        {
			if (ft_strcmp(meta->argument, "") != 0 && ft_strcmp(temp->argument, "") != 0 &&
				(meta->argument[ft_strlen(meta->argument) - 1] != ' ' && *(temp->argument) != ' '))
         		meta->argument = ft_strjoin(meta->argument, " ");
            meta->argument = ft_strjoin(meta->argument, temp->argument);
        }
        i = 1;
		if ((fd = redirect_command_head(check_meta, append, new)) == -1)
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
