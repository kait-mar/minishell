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

int        fd_connector(t_meta *head, char *str, char **env, int *status, int sig)
{
    pid_t pid;
    int statut;
    
    pipe(g_fd2);
    if ((pid = fork()) < 1)
    {
        ft_printf("%s\n", strerror(errno));
        return (-1);
    }
    else if (pid == 0)
    {
        printf("Entered to a child process\n");
        close(g_fd2[0]);
        if(dup2(g_fd2[1], 1) == -1)
        {
            ft_printf("Error in dup2 %s\n", strerror(errno));
            exit(EXIT_FAILURE);
        }
        head = head->next;
        printf("Head ==> %s\n", head->argument);
        built_in(head, str, env, status);
        close(g_fd2[1]);
        printf("In child of g_fd connector ==> %s\n", head->argument);
        exit(EXIT_SUCCESS);
    }
    else
    {
        close(g_fd2[1]);
        close(g_fd[1]);
        printf("Entered the parent g_fd connector\n");
        if (dup2(g_fd[0], 0) == -1)
        {
            ft_printf("Error in dup2 %s\n", strerror(errno));
            exit(EXIT_FAILURE);
        }
        printf("In Parent of g_fd connector ==> %s\n", head->argument);
        printf("Before Entering Child\n");
       /* if ((waitpid(pid, &statut, WUNTRACED))== -1)
        {
            ft_printf("Error in waitPid %s\n", strerror(errno));
            exit(EXIT_FAILURE);
        }*/
        char *s;
        //s = (char *) calloc(sizeof (char ), 10);
        //read(g_fd2[0], s, 10);
        printf("g_fd2 == > %s\n", s);
    }
    exit(EXIT_SUCCESS);
}

t_meta      *pipe_file(t_meta *head, char *str, char **env, int *status)
{
    pid_t pid;
    char *ss;

    ss = (char *) calloc(sizeof (char ), 100);
    if (ss == NULL)
        return (NULL);
    ft_printf("Entering in pipe_file\n");
    pipe(g_fd);
    if ((pid = fork()) < 0)
    {
        ft_printf("%s\n", strerror(errno));
        return (NULL);
    }
    else if (pid == 0)
    {
       ft_printf("Duplicate file descriptor\n");
       ft_printf("Before --> dup\n");
       if ((dup2(g_fd[1], 1)) == -1)
        {
            ft_printf("Error in dup2 %s\n", strerror(errno));
            exit(EXIT_FAILURE);
        }
       built_in(head, str, env, status);
       close(g_fd[1]);
       if (pipe_counter(head) > 1)
       {
           printf("before fd_connector \n");
           fd_connector(head, str, env, status, pid);
       }
       close(g_fd[0]);
       exit(EXIT_SUCCESS);
    }
    else
    {
        waitpid(pid, status, WUNTRACED);
        close(g_fd[1]);
        printf("HEERe\n");
       /* char *s;
        s = (char *) calloc(sizeof (char ), 10);
        read(g_fd2[0], s, 10);  close(g_fd[1]);
        printf("s ==> %s\n", s);*/
        if (dup2(g_fd[0], 0) == -1)
        {
            ft_printf("Error in dup2 %s\n", strerror(errno));
            exit(EXIT_FAILURE);
        }
        head = head->next;
        printf("In Parent =>> %s\n", head->argument);
        built_in(head, str, env, status);
        if (errno != 0)
            ft_printf("here");
        close(g_fd[0]);
    }
    return (head);
}