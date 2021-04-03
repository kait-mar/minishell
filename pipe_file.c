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

int    connecting(t_meta *head, char *str, char **env, int *status, int in , int out)
{
    pid_t pid;

    if ((pid = fork()) < 0)
    {
        ft_printf("Error in fork %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    if (pid == 0)
    {
        if (in != 0)
        {
            dup2(in, 0);
            close(in);
        }
        if (out != 1)
        {
            dup2(out, 1);
            close(out);
        }
        if (check_bin_echo(head->argument) == 1)
            head->command = 6;
        built_in(head, str, env, status, 0);
      /*  fprintf(stderr, "Errno ==> %d\n", errno);
        fprintf(stderr, "stats ==> %d\n", *status);
        fprintf(stderr, "head->arg ==> %s\n", head->argument);*/
        exit(EXIT_SUCCESS);
    }
    return (pid);
}

int  last_thing(t_meta *head, char *str,char **env, int *status, int in)
{
    if (in != 0)
    {
        dup2(in, 0);
        close(in);
    }
    built_in(head, str, env, status, 0);
    return (0);
}

t_meta      *pipe_file(t_meta *head, char *str, char **env, int *status)
{
    int fd[2];
    pid_t pid;
    t_meta *temp;
    int in;
    int old_stdin;

    old_stdin = dup(STDIN_FILENO);
    while(head->meta == '|')
    {
        if (head->next->meta == '\0' || head->next->meta == '|' || head->next->meta == ';')
        {
            pipe(fd);
            pid = connecting(head, str, env, status, in, fd[1]);
            close(fd[1]);
            in = fd[0];
            head = head->next;
        }
        else
            break ;
    }
    waitpid(-1, status, WNOHANG);
    close(fd[1]);
    if (head->next != NULL)
    {
        if (head->next->meta == '\0' || head->next->meta == ';')
            last_thing(head, str, env, status, in);
    }
    else
        last_thing(head, str, env, status, in);
    /* else if (head->next->meta == '>' || head->next->meta == '<')
         head = head->next; */
    close(fd[0]);
    dup2(old_stdin, 0);
    return (head);
}