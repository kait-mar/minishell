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
    int  fd[2];

    ft_printf("f wast pipe\n");
    if ((pid = fork()) < 0)
    {
        ft_printf("%s\n", strerror(errno));
        return ;
    }
    else if (pid == 0)
    {
        //ft_printf("f wast\n");
        //ft_printf(" meta --> %s\n", meta->argument);
        close(g_fd[1]);
        close(g_fd[2]);
        dup2(g_fd[0], 0);
        dup2(g_fd[3], 1);
        built_in(meta, str, env, status);
        close(g_fd[0]);
        close(g_fd[3]);
        //ft_printf("\n\n Second child ==> %s\n", meta->argument);
        exit(EXIT_SUCCESS);
    }
    else
    {
        waitpid(pid, status, WUNTRACED);
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
       //
        close(g_fd[2]);
        close(g_fd[1]);
        close(g_fd[3]);
        dup2(g_fd[1], 1);
        built_in(head, str, env, status);
        close(g_fd[1]);
        if (head->next->meta == '|') {
            head = head->next;
            n_pipe(head, str, env, status);
        }
        exit(EXIT_SUCCESS);
    }
    else
    {
        ft_printf("in parent");
        waitpid(pid, status, WUNTRACED);
        close(g_fd[1]);
        close(g_fd[3]);
        dup2(g_fd[2], 0);
        head = head->next->next;
        built_in(head, str, env, status);
        close(g_fd[2]);
        ft_printf("\n\nPArent head->argumet==> %s\n", head->argument);
    }
    return (head);
}