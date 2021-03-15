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

t_meta	*redirect_output(t_meta *meta, char *str, char **env, int *status)
{
	int		fd;
	int     i;
	int		pid;
	char    **split;
	t_meta	*temp;
	char	*new;

	temp = meta;
	i = 1;
	ft_printf("Here\n");
	while (temp->next != NULL && temp->meta == '>')
	{
		temp = temp->next;
		temp->argument = chang_dollar_sign(temp->argument, env);
		/*temp->argument = without_that(temp->argument, '\"');
		split = ft_split(temp->argument, ' ');
		free(temp->argument);
		temp->argument = NULL;
		temp->argument = ft_strdup(split[0]);
        while (split[i] != NULL)
        {
            split[i] = ft_strjoin(" ", split[i]);
			meta->argument = ft_strjoin(meta->argument, split[i]);
            i += 1;
        }*/
		new = file_name(temp->argument);
        temp->argument = temp->argument + ft_strlen(new);
        //new = remove_staring_quote(new);
		new = final_file_name(new);
        meta->argument = ft_strjoin(meta->argument, " ");
        meta->argument = ft_strjoin(meta->argument, temp->argument);
        i = 1;
		if ((fd = open(new,  O_RDWR | O_CREAT | O_TRUNC, S_IRWXU)) < 0)
		{
			ft_putstr(strerror(errno));
			return (NULL);
		}
	}
	pid = fork();
	if (pid < 0)
		ft_putstr(strerror(errno));
	else if (pid == 0)
	{
		if ((dup2(fd, STDOUT_FILENO) != -1))
		{
			built_in(meta, str, env, status, 0);
			close(fd);
			exit(EXIT_SUCCESS);
		}
		else
		{
			ft_putstr(strerror(errno));
			close(fd);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		if ((waitpid(pid, status, WUNTRACED) == -1))
			ft_putstr(strerror(errno));
		close(fd);
	}
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