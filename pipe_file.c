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


int        fd_connector(t_meta *head, char *str, char **env, int *status, int sig)
{
    pid_t pid;

    if ((pid = fork()) < 1)
    {
        ft_printf("%s\n", strerror(errno));
        return (-1);
    }
    else if (pid == 0)
    {
        printf("Entered to a child process\n");
        close(g_fd[0]);
        if(dup2(g_fd[1], 1) == -1)
        {
            ft_printf("Error in dup2 %s\n", strerror(errno));
            exit(EXIT_FAILURE);
        }
        close(g_fd[1]);
        exit(EXIT_SUCCESS);
    }
    else
    {
        close(g_fd[1]);
        if (dup2(g_fd[0], 0) == -1)
        {
            ft_printf("Error in dup2 %s\n", strerror(errno));
            exit(EXIT_FAILURE);
        }
        built_in(head, str, env, status);
        close(g_fd[0]);
        printf("Before Entering Child\n");
        waitpid(pid, status, WUNTRACED);
    }
    exit(EXIT_SUCCESS);
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
        close(g_fd[0]);
       ft_printf("Duplicate file descriptor\n");
       if (dup2(g_fd[1], 1) == -1)
       {
           ft_printf("Error in dup2 %s\n", strerror(errno));
           exit(EXIT_FAILURE);
       }
       built_in(head, str, env, status);
       close(g_fd[1]);
       fd_connector(head, str, env, status, pid);
       exit(EXIT_SUCCESS);
    }
    else
    {
        waitpid(pid, status, WUNTRACED);
        close(g_fd[1]);
        if (dup2(g_fd[0], 0) == -1)
        {
            ft_printf("Error in dup2 %s\n", strerror(errno));
            exit(EXIT_FAILURE);
        }
        built_in(head, str, env, status);
        close(g_fd[0]);
    }
    return (head);
}