/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kait-mar <kait-mar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 09:10:20 by kait-mar          #+#    #+#             */
/*   Updated: 2021/01/09 12:24:39 by kait-mar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	inter_signal(int signum)
{
	printf("\nCTR-C is pressed, and my pid is %d and my parent pid is %d \n", getpid(), getppid());
	//print("my pid is %d\n", getpid());
	//print("and my parent pid is %d\n", getppid());
	kill(getpid(), SIGTERM);
	//exit(EXIT_SUCCESS);
}

void	quit_signal(int signum)
{
	printf("\nCTR-D is pressed\n");
	exit(EXIT_SUCCESS);
}

void	signal_handler(int signum)
{
	signal(SIGINT, inter_signal);
	signal(SIGQUIT, quit_signal);
}
