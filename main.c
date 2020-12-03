/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molabhai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 18:18:33 by molabhai          #+#    #+#             */
/*   Updated: 2020/12/01 19:05:06 by molabhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		main()
{
/*	DIR *dir;
	struct dirent *dirent;*/
/*	pid_t pid1;
	int status;

	status = 0;
	printf("Parent Process PID == > %d\n", getpid());
	pid1 = fork();
	if (pid1 == 0)
	{
		printf("Child Process PID == > %d\n", getpid());
		exit(status);
	}
	else {
		printf("Process is == > %d check == > %d\n", getpid(), pid1);
		wait(&status);
	}
	printf("status ==> %d\n", status);*/
/*
	printf("Here\n");
	dir = opendir("Libft");
	if (dir != NULL)
	{
		while((dirent = readdir(dir)) != NULL)
		{
			printf("%s ", dirent->d_name);
		}
	}
	if (chdir("Libft") == 0)
		ft_putstr("Has Changed Directory\n");
	else {
		ft_putstr("Error");
	}*/
	cd_command();
	return(0);
}
