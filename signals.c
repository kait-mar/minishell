/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kait-mar <kait-mar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 09:10:20 by kait-mar          #+#    #+#             */
/*   Updated: 2021/01/12 12:14:59 by kait-mar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		inter_signal(int signum)
{
	printf("\nCTR-C is pressed\n");
	//print("my pid is %d\n", getpid());
	//print("and my parent pid is %d\n", getppid());
	if (g_process == 0)
	{
		printf("before ignoring the g_process is %d\n", g_process);
		printf("the signal is ignored\n");
		//signal(SIGINT, SIG_IGN);
		printf("after ignoring the g_process is %d\n", g_process);
		g_process = 0;
		return (0);
	//	exit(EXIT_SUCCESS);
	}
	else
	{
		printf("the signal is handled\n");
		kill(g_process, SIGKILL);
		g_process = 0;
		return (1);
	}
	printf("before returning\n");
}

void	quit_signal(int signum)
{
	printf("\nCTR-D is pressed\n");
	exit(EXIT_SUCCESS);
}

void	signal_handler(int signum)
{
	if (signal(SIGINT, inter_signal) == 0)
	{
		printf("before termination signal handler\n");
		return ;
	}
	//signal(SIGQUIT, quit_signal);
}
