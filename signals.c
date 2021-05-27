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

void	inter_signal(int status)
{
	g_global.signal_input = 1;
	g_global.in_signal = 1;
	if (g_global.on == 1)
	{
		kill(1, SIGINT);
	}
	if (g_global.on == 1)
	{
		g_process = 0;
		write(1, "\n", 1);
	}
	else
	{
		prompt();
	}
}

void	quit_signal(int signum)
{
	if (g_global.on == 1)
	{
		kill(1, SIGQUIT);
		ft_printf("Quit: 3\n");
	}
}

void	signal_handler(int *status)
{
	signal(SIGINT, inter_signal);
	signal(SIGQUIT, quit_signal);
}
