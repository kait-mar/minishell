/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_append.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molabhai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 11:13:33 by molabhai          #+#    #+#             */
/*   Updated: 2021/01/02 10:06:39 by molabhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_meta  *append_file(t_meta *meta, char *str, char **env, int *status)
{
    int fd;
    //char *output_from;
    char **split;
    char *output_to;
    pid_t pid;
    t_meta *head;
    int i;

    head = meta;
    i = 0;
    //output_from = ft_strdup(head->argument);
    while (head->meta_append != 0)
    {
        head = head->next;
        i += 1;
     //   output_to = head->argument;
        output_to = ft_strtrim(head->argument, " ");
        output_to = chang_dollar_sign(output_to, env);
        output_to = without_that(output_to, '\"');
        split = ft_split(output_to, ' ');
        free(output_to);
        output_to = NULL;
        output_to = ft_strdup(split[0]);
        while (split[i] != NULL)
        {
            split[i] = ft_strjoin(" ", split[i]);
            meta->argument = ft_strjoin(meta->argument, split[i]);
            i += 1;
        }
        i = 1;
        if ((fd = open(output_to, O_CREAT | O_APPEND | O_RDWR, S_IRWXU)) == -1)
        {
            ft_printf("%s", strerror(errno));
            return (NULL);
        }
    }
    if ((pid = fork()) < 0)
        ft_printf("%s\n", strerror(errno));
    else if (pid == 0)
    {
        if (dup2(fd, 1) == -1)
            ft_printf("%s\n", strerror(errno));
        built_in(meta, str, env, status, 0i);
        close(fd);
        exit(EXIT_SUCCESS);
    }
    else
    {
        if (waitpid(pid, status, WUNTRACED) == -1)
            ft_printf("Error has occured\n");
        close(fd);
    }
    while (i  != 0)
    {
        meta = meta->next;
        i -= 1;
    }
    return (meta);
}