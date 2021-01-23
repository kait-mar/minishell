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
    int in;
    t_std *std;
    t_std *tmp;
    t_std *temp;
    t_meta *test;

    cmd = pipe_counter(head) + 1;

    test = head;
    if (!(std = (t_std *) malloc(sizeof (t_std))))
        return NULL;
    int pid_d = 0;
   while (test->meta == '|')
   {
       pipe(fd);
       fprintf(stderr, "%d: fd[0] = %d, fd[1] = %d\n", i, fd[0], fd[1]);
       if (i == 0)
       {
           std->in = fd[0];
           std->out = fd[1];
           std->index = i;
           std->next = NULL;
           tmp = std;
       }
       else
       {
           if (!(temp = (t_std *) malloc(sizeof (t_std))))
               return NULL;
           temp->out = fd[1];
           temp->in = fd[0];
           temp->index = i;
           while (tmp->next)
               tmp = tmp->next;
           tmp->next = temp;
           tmp->next->next = NULL;
       }
       test = test->next;
       i = i + 1;
   }
   i = 0;
    while (head->meta == '|')
    {
        if ((pid = fork()) < 0)
        {
            printf("Error in fork ");
            exit(EXIT_FAILURE);
        }
        else if (pid == 0)
        {
            if (i > 0)
            {
                if (pid_d > 0)
                    fprintf(stderr, "\nYes it's bigger\n");
                fprintf(stderr, "In Between\n");
                fprintf(stderr, "child %d: close(%d)\n", pid_d, std->out);
                close(std->out);
                fprintf(stderr, "child %d: dup2(%d, %d)\n", pid_d, std->in, 0);
                if (dup2(std->in, 0) == - 1)
                {
                    printf("Error in dup2 %s\n", strerror(errno));
                    exit(EXIT_FAILURE);
                }
                std = std->next;
                if (pid_d == 0)
                {
                    fprintf(stderr, "child %d: dup2(%d, %d)\n", pid_d, std->out, 1);
                    if (dup2(std->out, 1) == - 1)
                    {
                        printf("Error in dup2 %s\n", strerror(errno));
                        exit(EXIT_FAILURE);
                    }
                    built_in(head, str, env, status);
                    fprintf(stderr, "child %d: close(%d)\n", pid_d, std->out);
                    close(std->out);
                    close(std->in);
                    exit(EXIT_SUCCESS);

                }
            }
            else if (i == 0)
            {
                fprintf(stderr, "\nFirst Command\n");
                fprintf(stderr, "child %d: close(%d)\n", pid_d, std->in);
                close(std->in);
                fprintf(stderr, "child %d: dup2(%d, %d)\n", pid_d, std->out, 1);
                if (dup2(std->out, 1) == - 1)
                {
                    printf("Error in dup2 %s\n", strerror(errno));
                    exit(EXIT_FAILURE);
                }
                built_in(head, str, env, status);
                fprintf(stderr, "child %d: close(%d)\n", pid_d, std->out);
                close(std->out);
               // exit(EXIT_SUCCESS);
            }

        }
        pid_d = pid;
        head = head->next;
        i = i + 1;
    }
    waitpid(pid, status, WUNTRACED);
    while (std->next != NULL)
        std = std->next;
    close(std->out);
    printf("End of Process\n");
    printf("std_index == > %d\n", std->index);
    printf("std->in == %d\n", std->in);
    printf("std->out == %d\n", std->out);
    //head = head->next;
    printf("cmd ==> %d\n", head->command);
    if (dup2(std->in, 0) == - 1)
    {
        printf("Error in dup2 %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    built_in(head, str, env, status);
    close(std->in);
    return (head);
}