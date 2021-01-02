/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_output.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kait-mar <kait-mar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 10:07:34 by kait-mar          #+#    #+#             */
/*   Updated: 2021/01/02 18:23:25 by kait-mar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_meta	*redirect_output(t_meta *meta, char *str, char **env, int *status)
{
    int fd;
    int pid;


	while (meta->next != NULL && meta->meta == '>')
	{
		printf("==> %s\n", meta->argument);
		meta = meta->next;
		printf("==> %s\n", meta->argument);
		if ((fd = open(meta->argument,  O_RDWR | O_CREAT, S_IRWXU)) < 0)
		{
			ft_putstr(strerror(errno));
			printf("Here\n");
			//exit(EXIT_FAILURE);
		}
		printf("here 1\n");
	}
	//printf("the out argument %s\n", meta->argument);
	if ((pid = fork()) < 0)
		ft_putstr(strerror(errno));
	else if (pid == 0)
	{
		if ((dup2(fd, STDOUT_FILENO) == -1))
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
		close(fd);
	}
	printf("Before");
	//meta = meta->next;
	printf("After");
	return (meta);
}