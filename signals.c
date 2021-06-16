#include "minishell.h"

void	inter_signal(int status)
{
	status = 0;
	g_global.signal_input = 1;
	g_global.in_signal = 1;
	if (g_global.on == 1)
	{
		kill(1, SIGINT);
		*g_global.status = 130;
		g_global.s_status = 1;
	}
	if (g_global.on == 1)
		write(1, "\n", 1);
	else
	{
		prompt();
	}
}

void	quit_signal(int signum)
{
	signum = 0;
	if (g_global.on == 1)
	{
		kill(1, SIGQUIT);
		*g_global.status = 131;
		g_global.s_status = 1;
		ft_printf("Quit: 3\n");
	}
}

void	signal_handler(void)
{
	signal(SIGINT, inter_signal);
	signal(SIGQUIT, quit_signal);
}
