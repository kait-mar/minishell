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

t_meta      *pipe_file(t_meta *head, char *str, int *status)
{
    int pipe_fd[2];
    int pid;

    pipe(pipe_fd);
    if ((pid = fork()) < 0)
    {
        ft_printf("%s\n", strerror(errno));
        return (NULL);
    }
    else if (pid == 0)
    {
        writ
    }
}