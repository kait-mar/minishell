/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molabhai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 14:22:30 by molabhai          #+#    #+#             */
/*   Updated: 2021/01/03 14:22:34 by molabhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

t_meta      *pipe_file(t_meta *head, char *str, char **env, int *status)
{
    int pid;
    t_pipe  *s;
    int i;

    pipe(g_fd);
    i = 0;
    if ((pid = fork()) < 0)
    {
        ft_printf("%s\n", strerror(errno));
        return (NULL);
    }
    else if (pid == 0)
    {
        close(g_fd[0]);
        s = built_in(head, str, env, status);
        if (s->command == 1 || s->command == 2)
            write(g_fd[1], s->s_pipe, ft_strlen(s->s_pipe));
        else if (s->command == 3)
        {
            while (s->c_pipe[i])
            {
                write(g_fd[1], s->c_pipe[i], ft_strlen(s->c_pipe[i]));
                i += 1;
            }
        }
        exit(EXIT_SUCCESS);
    }
    else
    {
        wait(NULL);
        close(g_fd[1]);
        s = built_in(head, str, env, status);
        if (s->command == 1 || s->command == 2)
            read(g_fd[1], str, ft_strlen(s->s_pipe));
        else if (s->command == 3)
        {
            while (s->c_pipe[i])
            {
                read(g_fd[1], s->c_pipe[i], ft_strlen(s->c_pipe[i]));
                i += 1;
            }
        }
        close(g_fd[0]);
    }
    head = head->next;
    head->argument = ft_strjoin(head->argument, s->s_pipe);
    built_in(head, str, env, status);
    return (head);
}