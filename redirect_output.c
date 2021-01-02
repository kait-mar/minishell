/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_output.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kait-mar <kait-mar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 10:07:34 by kait-mar          #+#    #+#             */
/*   Updated: 2021/01/02 11:23:39 by kait-mar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    redirect_output(t_meta *meta, char *str, char **env, int *status)
{
    int fd;
    int pid;
    int newfd;

    if ((fd = open(meta->next->argument,  O_RDWR | O_CREAT, S_IRWXU)) >= 0)
    {
		printf("yes\n");
		if ((pid = fork()) < 0)
		    ft_printf("%s\n", strerror(errno));
		else if (pid == 0)
        {
            if (dup2(fd, STDOUT_FILENO) != -1)
                built_in(meta, str, env, status);
            else
            {
                ft_putstr(strerror(errno));
                exit(EXIT_FAILURE);
            }
            close(fd);
            exit(EXIT_SUCCESS);
        }
		else
        {
		    if ((waitpid(pid, status, WUNTRACED) == -1))
		        printf("%s\n", strerror(errno));
		    printf("Parent Process");
            close(fd);
        }
    }
    //meta = meta->next;
	printf("it has returned");
}