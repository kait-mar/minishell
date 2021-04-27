/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molabhai <molabhai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 18:18:33 by molabhai          #+#    #+#             */
/*   Updated: 2021/03/10 15:28:59 by molabhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	built_in(t_meta *meta, t_assen assen, char **env)
{
	int	exept;

	exept = 0;
	if (meta->command == 1)
		cd_command(meta->argument, g_global.status, env);
	else if (meta->command == 2)
		pwd_command(g_global.status, exept);
	else if (meta->command == 3)
		env_command(env, meta, g_global.status);
	else if (meta->command == 4)
		export_command(env, meta->argument, g_global.status, NULL);
	else if (meta->command == 5)
		unset_command(env, meta->argument, g_global.status);
	else if (meta->command == 6)
		echo(meta->argument, env, g_global.status);
	else if (meta->command == 0)
	{
		if (ft_strcmp(meta->argument, "") != 0)
		{
			g_process = 1;
			execut_command(env, meta->argument, g_global.status);
		}
	}
	if (meta->command == 7)
		exit_command(g_global.status, meta->argument, &assen);
}

void	prompt(void)
{
	char	s[100];

	getcwd(s, 100);
	if (g_global.in_signal == 1)
	{
		ft_printf("\n%s ", s);
	}
	else if (g_global.in_signal == 0)
		ft_printf("%s ", s);
	g_global.in_signal = 0;
}

int	check_wich_command(char *str)
{
	int	exept;

	exept = 0;
	if (ft_strncmp(str, "cd", 2) == 0 && (ft_isalpha(str[2]) == 0))
		return (1);
	if (check_pwd(str, &exept) == 0)
		return (2);
	if (check_env(str) == 0)
		return (3);
	if (ft_strncmp(str, "export", 6) == 0 && (ft_isalpha(str[6]) == 0))
		return (4);
	if (check_unset(str) == 0)
		return (5);
	if (echo_strcmp(str, "echo") == 0)
		return (6);
	if (check_exit(str) == 1)
		return (7);
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_assen	assen;

	memset(&assen, 0, sizeof (assen));
	assen = minishell_init(env);
	minishell(av, env, assen);
	return (*(g_global.status));
}
