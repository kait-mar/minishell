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
        built_in(head, str, env, status, 1);
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
        built_in(head, str, env, status, 0);
        close(g_fd2[0]);
    }
    exit(EXIT_SUCCESS);
}

void	ft_lstadd_std(t_std **alst, t_std *new)
{
    t_std *lst;

    if (*alst == NULL)
        *alst = new;
    else
    {
        lst = *alst;
        while (lst->next)
            lst = lst->next;
        lst->next = new;
    }
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
    t_std *temp;
    t_meta *test;
    int     fd1[2];
    int     fd2[2];

    cmd = pipe_counter(head) + 1;
    fprintf(stderr, "The parent pid ==> %d\n", getpid());
    test = head;
    if (!(std = (t_std *) malloc(sizeof (t_std))))
        return NULL;
   while (test->meta == '|')
   {
       pipe(fd);
       if (i == 0)
       {
           std->in = fd[0];
           std->out = fd[1];
           std->index = i;
           std->next = NULL;
       }
       else
       {
          if (!(temp = (t_std *) malloc(sizeof (t_std))))
               return NULL;
           temp->out = fd[1];
           temp->in = fd[0];
           temp->index = i;
           temp->next = NULL;
           ft_lstadd_std(&std, temp);
       }
       if (i == 0)
           fprintf(stderr, "%d: fd[0] = %d, fd[1] = %d\n", std->index, std->in, std->out);
       if (i > 0)
        fprintf(stderr, "%d: fd[0] = %d, fd[1] = %d\n", std->next->index, std->next->in, std->next->out);
       test = test->next;
       i = i + 1;
   }
   i = 0;
   int  check = 0;
    char *s = calloc(1, 100);
    while (head->meta == '|')
    {
        if (dup2(std->out, STDOUT_FILENO) == - 1)
        {
            fprintf(stderr, "Error in dup2 %s\n", strerror(errno));
            exit(EXIT_SUCCESS);
        }
        if (head->command != 0)
            built_in(head, str, env, status, 0);
        else
            execut_command(env, str, &check, 0);
        read(0, s, 10);
        fprintf(stderr, "s ==> %s\n", s);
        head = head->next;
        i += 1;
    }
    fprintf(stderr, "exit head ==> %s\n", head->argument);
    fprintf(stderr, "exit head ==> %c\n", head->meta);
    return (head);
}