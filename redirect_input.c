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

#include "minishell.h"

t_meta	*redirect_intput(t_meta *meta, t_assen assen, char **env, int *status)
{
	int		fd;
	int		pid;
	char	*new;
	t_meta	*temp;
	int		on;

	temp = meta;
	on = 0;
	while (temp->next != NULL && temp->meta == '<')
	{
		temp = temp->next;
        temp->argument = chang_dollar_sign(temp->argument, env);

		new = file_name(temp->argument);
        temp->argument = temp->argument + ft_strlen(new);
		if (*(temp->argument) == ' ')
			(temp->argument)++;
          if (meta->command == 0 && check_wich_command(take_first_word(temp->argument)) != 0 && on == 0)
        {
            meta = temp;
            meta->command = check_wich_command(take_first_word(ft_strtrim(temp->argument, " ")));
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


		if ((fd = open(new, O_RDWR, S_IRWXU)) < 0)
		{
			g_in_redirect = 1;
			ft_printf("minishell: %s: %s", new, strerror(errno));
			return (NULL);
		}
	}
	pid = fork();
	if (pid < 0)
		ft_putstr(strerror(errno));
	else if (pid == 0)
	{
		if ((dup2(fd, STDIN_FILENO) != -1))
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
