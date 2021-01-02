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
    int newfd;
    if ((fd = open(meta->next->argument,  O_WRONLY | O_CREAT)) >= 0)
    {
		printf("yes\n");
        if (dup2(fd, STDOUT_FILENO) != -1)
        {
			built_in(meta, str, env, status);
			//exit(EXIT_SUCCESS);
		}
		else
		{
			ft_putstr(strerror(errno));
			return ;
		}
		close(fd);
    }
    //meta = meta->next;
	printf("it has returned");
}