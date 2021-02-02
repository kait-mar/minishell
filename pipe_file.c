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
        built_in(head, str, env, status, 1);
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
        pipe(fd);
        pid = connecting(head, str, env, status, in, fd[1]);
        close(fd[1]);
        in = fd[0];
        head = head->next;
    }
    waitpid(pid, status, WUNTRACED);
    close(fd[1]);
    last_thing(head, str, env, status, in);
    close(fd[0]);
    dup2(old_stdin, 0);
    return (head);
}