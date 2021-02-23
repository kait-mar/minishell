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

void		inter_signal(int status)
{
    g_in_signal = 1;
	if (g_on == 1)
	    kill(g_pid, SIGINT);
	if (g_on == 1)
	{
        g_process = 0;
        prompt(2);
    }
	else
	    prompt(g_in_signal);
}

void	quit_signal(int signum)
{
    if (g_on == 1)
    {
        kill(g_pid, SIGQUIT);
        ft_printf("Quit: 3\n");
    }
}

void	signal_handler(int *status)
{
	signal(SIGINT, inter_signal);
	signal(SIGQUIT, quit_signal);
	//printf("before termination signal handler\n");
}