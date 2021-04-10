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
		//check this if put it in or outside the loop
		on = 0;
		append = 0;
		check_meta = 0;
		if (temp->meta_append != 0)
			append = 1;
		else if (temp->meta == '>')
			check_meta = '>';
        //ft_printf("temp->command ==> %d || temp->arg ==> %s\n", temp->command, temp->argument);
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
		if (*(temp->argument) == ' ')
			(temp->argument)++;
          if (meta->command == 0 && check_wich_command(take_first_word(temp->argument)) != 0 && on == 0)
        {
			//temp->argument = temp->argument + 1;
            meta = temp;
            meta->command = check_wich_command(take_first_word(temp->argument));
           // ft_printf("in temp->command ==> %d || temp->arg ==> %s\n", meta->command, meta->argument);
            on = 1;
        }
        //new = remove_staring_quote(new);
        new = final_file_name(new);
        if (on == 0)
        {
			if (ft_strcmp(meta->argument, "") != 0 && ft_strcmp(temp->argument, "") != 0 &&
				(meta->argument[ft_strlen(meta->argument) - 1] != ' ' && *(temp->argument) != ' '))
         		meta->argument = ft_strjoin(meta->argument, " ");
            meta->argument = ft_strjoin(meta->argument, temp->argument);
        }
       // ft_printf("out  temp->command ==> %d || temp->arg ==> %s\n", meta->command, meta->argument);
        i = 1;
		if (append != 0)
		{
			if ((fd = open(new, O_CREAT | O_APPEND | O_RDWR, S_IRWXU)) == -1)
			{
				ft_printf("%s", strerror(errno));
				return (NULL);
			}
		}
		else if (check_meta == '>')
		{
			if ((fd = open(new,  O_RDWR | O_CREAT | O_TRUNC, S_IRWXU)) < 0)
			{
				ft_putstr(strerror(errno));
				return (NULL);
			}
		}
	}
	pid = fork();
	if (pid < 0)
		ft_putstr(strerror(errno));
	else if (pid == 0)
	{
		if ((dup2(fd, STDOUT_FILENO) != -1))
		{
			built_in(meta, assen, env, status);
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
