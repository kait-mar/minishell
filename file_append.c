/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_append.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molabhai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 11:13:33 by molabhai          #+#    #+#             */
/*   Updated: 2020/12/29 11:13:35 by molabhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_meta  *append_file(t_meta *meta, char *str, char **env, int status)
{
    int fd;
    char *output_from;
    char *output_to;
    pid_t pid;
    t_meta *head;
    int i;

    head = meta;
    output_from = ft_strdup(head->argument);
    head = head->next;
    output_to = ft_strdup(head->argument);
    output_to = ft_strtrim(output_to, " ");
    fd = open(output_to, O_CREAT | O_APPEND | O_RDWR, S_IRWXU);
    if ((pid = fork()) < 0)
        ft_printf("%s\n", strerror(errno));
    else if (pid == 0)
    {
        if ((i = dup2(fd, 1)) == -1)
            ft_printf("%s\n", strerror(errno));
        built_in(meta, str, env, status);
        close(fd);
        exit(EXIT_SUCCESS);
    }
    else
    {
        if (waitpid(pid, &status, WUNTRACED) == -1)
            ft_printf("Error has occured\n");
        close(fd);
    }
    meta = meta->next;
    return (meta);
}