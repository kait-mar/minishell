/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kait-mar <kait-mar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 14:22:30 by molabhai          #+#    #+#             */
/*   Updated: 2021/01/20 10:39:58 by kait-mar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"


int         pipe_counter(t_meta *head)
{
    int     i;

    i = 0;
    while (head != NULL && head->meta == '|')
    {
        i += 1;
        head = head->next;
    }
    return (i);
}

int        fd_connector(t_meta *head, char *str, char **env, int *status, int sig) {
    pid_t pid;
    int statut;

    if ((pipe(g_fd2)) == -1)
    {
        ft_printf("Error in dup2 \"%s\" \n");
        exit(EXIT_FAILURE);
    }
    if ((pid = fork()) < 0)
    {
        ft_printf("%s\n", strerror(errno));
        return (-1);
    }
    else if (pid == 0)
    {
        close(g_fd2[0]);
        if ((dup2(g_fd2[1], 1)) == -1)
        {
            ft_printf("Error in dup2 \"%s\"\n", strerror(errno));
            exit(EXIT_FAILURE);
        }
        built_in(head, str, env, status);
        close(g_fd2[1]);
        exit(EXIT_SUCCESS);
    }
    else
    {
      // wait(NULL);
        close(g_fd2[1]);
        if ((dup2(g_fd2[0], 0)) == -1)
        {
            ft_printf("Error in dup2 \"%s\"\n", strerror(errno));
            exit(EXIT_FAILURE);
        }
        if ((dup2(g_fd[1], 1) == -1))
        {
            ft_printf("Error in dup2 \"%s\"\n", strerror(errno));
            exit(EXIT_FAILURE);
        }
        head = head->next;
        built_in(head, str, env, status);
        close(g_fd2[0]);
    }
    exit(EXIT_SUCCESS);
}

t_meta      *pipe_file(t_meta *head, char *str, char **env, int *status) {
    pid_t pid;
    char *ss;

    ss = (char *) calloc(sizeof(char), 100);
    if (ss == NULL)
        return (NULL);
    ft_printf("Entering in pipe_file\n");
    if ((pipe(g_fd)) == -1)
    {
        ft_printf("Error in dup2 \"%s\" \n");
        exit(EXIT_FAILURE);
    }
    if ((pid = fork()) < 0)
    {
        ft_printf("%s\n", strerror(errno));
        return (NULL);
    }
    else if (pid == 0)
    {
        close(g_fd[0]);
        if (pipe_counter(head) > 1)
        {
            ft_printf("\n fd Connector \n");
            fd_connector(head, str, env, status, pid);
        }
        else
        {
            ft_printf("Entering else\n");
            if ((dup2(g_fd[1], 1))  == -1)
            {
                ft_printf("Error in dup2 \"%s\"\n", strerror(errno));
                exit (EXIT_FAILURE);
            }
            built_in(head, str, env, status);
            close(g_fd[1]);
        }
        exit (EXIT_SUCCESS);
    }
    else
    {
        waitpid(pid, status, WUNTRACED);
        ft_printf("In parent\n");
        close(g_fd[1]);
        if ((dup2(g_fd[0], 0)) == -1)
        {
            ft_printf("Error in dup2 \"%s\"\n", strerror(errno));
            exit (EXIT_FAILURE);
        }
        head = head->next;
        built_in(head, str, env, status);
        close(g_fd[0]);
    }
    return (head);
}
