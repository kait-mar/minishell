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
        waitpid(pid, status, WUNTRACED);
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

t_meta      *pipe_file(t_meta *head, char *str, char **env, int *status)
{
    int     index;
    int     fd_nmbr;
    int     cmd;
    int     first_time = 0;
    int     fd[2];
    int     pid;
    int i = 0;
    t_index   *ind;
    t_index     *tmp;
    t_index     *temp;

    cmd = pipe_counter(head) + 1;
    if (!(ind = (t_index *) malloc(sizeof (t_index))))
        return NULL;
    printf("Here\n");
    while (head->meta == '|')
    {
        printf("Here\n");
        if (!(temp = (t_index *) malloc(sizeof (t_index))))
            return NULL;
        if (i == 0)
        {
           pipe(ind->fd);
            ind->next = NULL;
           tmp = ind;
        }
        else
        {
            pipe(temp->fd);
            while (tmp->next)
                tmp = tmp->next;
            tmp->next = temp;
            tmp->next->next = NULL;
        }
        if ((pid = fork()) < 0)
        {
            printf("Error in fork ");
            exit(EXIT_FAILURE);
        }
        else if (pid == 0)
        {
            if (i > 0)
            {
                printf("In i > 0 Enters\n");
                printf("cmd == %d\n", head->command);
                if (dup2(ind->fd[0], 0) == - 1)
                {
                    printf("Error in dup2 %s\n", strerror(errno));
                    exit(EXIT_FAILURE);
                }
                ind = ind->next;
                if (dup2(ind->fd[1], 1) == - 1)
                {
                    printf("Error in dup2 %s\n", strerror(errno));
                    exit(EXIT_FAILURE);
                }
                built_in(head, str, env, status);
                close(ind->fd[0]);
                close(ind->fd[1]);
                exit(EXIT_SUCCESS);
            }
            else
            {
                printf("In i == 0 Enters\n");
                printf("cmd == %d\n", head->command);
                close(ind->fd[0]);
                if (dup2(ind->fd[1], 1) == - 1)
                {
                    printf("Error in dup2 %s\n", strerror(errno));
                    exit(EXIT_FAILURE);
                }
                built_in(head, str, env, status);
                close(ind->fd[1]);
                exit(EXIT_SUCCESS);
            }
        }
        printf("Argument ==> %d\n", head->command);
        head = head->next;
        i = i+ 1;
    }
    waitpid(pid, status, WUNTRACED);
    printf("End of Process\n");
    head = head->next->next;
    close(fd[1]);
    if (dup2(fd[0], 0) == - 1)
    {
        printf("Error in dup2 %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    close(fd[0]);
    return (head);
}
