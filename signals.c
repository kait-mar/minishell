/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kait-mar <kait-mar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 09:10:20 by kait-mar          #+#    #+#             */
/*   Updated: 2021/01/19 15:47:58 by kait-mar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		inter_signal(int on)
{
	int	pid;
    int statut;

    //printf("\nCTR-C is pressed\n");
    on = 1;
	if ((pid = fork()) < 0)
		printf("error in fork signal : %s\n", strerror(errno));
	else if (pid == 0)
	{
		//printf("in Child\n");
		if (g_process == 0)
		{
			//printf("the signal is ignored\n");
			g_process = 0;
		}
		else
		{
			//printf("the signal is handled\n");
			kill(g_process, SIGKILL);
			g_process = 0;
		}
		exit(EXIT_SUCCESS);
	}
	else
	{
		//printf("in parent\n");
		if (waitpid(pid, &statut, WUNTRACED) == -1)
			printf("error in waipid signal : %s\n", strerror(errno));
	}
	prompt(2);
}

void	quit_signal(int signum)
{
	printf("\nCTR-D is pressed\n");
	exit(EXIT_SUCCESS);
}

void	signal_handler(int *status, int *on)
{
    *on = 1;
	signal(SIGINT, inter_signal);
	signal(SIGQUIT, inter_signal);
	//printf("before termination signal handler\n");
}
