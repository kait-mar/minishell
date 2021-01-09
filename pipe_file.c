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

void        n_pipe(t_meta *meta, char *str, char **env, int *status)
{
    pid_t pid;

    if ((pid = fork()) < 0)
    {
        ft_printf("%s\n", strerror(errno));
        return ;
    }
    else if (pid == 0)
    {
        close(g_fd[0]);
        dup2(g_fd[1], 1);
        built_in(meta, str, env, status);
        close(g_fd[1]);
        exit(EXIT_SUCCESS);
    }
    else
    {
        close(g_fd[1]);
        dup2(fd[0], 0);
        built_in(meta, str, env, status);
        close(g_fd[0]);
        wait(NULL);
    }
}

t_meta      *pipe_file(t_meta *head, char *str, char **env, int *status)
{
    pid_t pid;
    int i;
    char *ss;

    ss = (char *) calloc(sizeof (char ), 100);
    if (ss == NULL)
        return (NULL);
    pipe(g_fd);
    i = 0;
        if ((pid = fork()) < 0)
        {
            ft_printf("%s\n", strerror(errno));
            return (NULL);
        }
        else if (pid == 0)
        {
            if (dup2(g_fd[1], 1) == -1)
                exit(EXIT_FAILURE);
            built_in(head, str, env, status);
            if (head->next->meta == '|')
                n_pipe(head, str, env, status);
            close(g_fd[0]);
            close(g_fd[1]);
            exit(EXIT_SUCCESS);
        }
        else
        {
            wait(NULL);

            close(g_fd[1]);
            head = head->next;
            dup2(g_fd[0], 0);
            built_in(head, str, env, status);
            close(g_fd[0]);
        }
    return (head);
}