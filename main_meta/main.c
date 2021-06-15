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

#include "../minishell.h"

void	built_in(t_meta *meta, t_assen assen, char **env)
{
	int	exept;

	exept = 0;
	ft_memset(&assen, 0, sizeof(assen));
	if (meta->command == 1)
		cd_command(meta->argument, g_global.status, env);
	else if (meta->command == 2)
		pwd_command(g_global.status, exept);
	else if (meta->command == 3)
		env_command(env, meta, g_global.status);
	else if (meta->command == 4)
		export_command(env, meta->argument, NULL);
	else if (meta->command == 5)
		unset_command(env, meta->argument, g_global.status);
	else if (meta->command == 6)
		echo(meta->argument, env, g_global.status);
	else if (meta->command == 0)
	{
		if (ft_strcmp(meta->argument, "") != 0)
			execut_command(env, meta->argument, g_global.status);
	}
	if (meta->command == 7)
		exit_command(g_global.status, meta->argument);
}

void	prompt(void)
{
	if (g_global.in_signal == 1)
		ft_printf("\nminishell> ");
	else if (g_global.in_signal == 0)
		ft_printf("minishell> ");
	g_global.in_signal = 0;
}

int	check_wich_command(char *str)
{
	if (echo_strcmp(str, "/bin/echo") == 0)
		return (6);
	if (ft_strncmp(str, "cd", 2) == 0 && (ft_isalpha(str[2]) == 0))
		return (1);
	if (ft_strncmp(str, "pwd", 3) == 0 && ft_isalpha(str[3]) == 0)
		return (2);
	if (ft_strncmp(str, "env", 3) == 0 && ft_isalpha(str[3]) == 0)
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

int	match_shlvl(char *env, char *sh)
{
	int	i;

	i = 0;
	while (env[i] && sh[i] && env[i] != '=')
	{
		if (env[i] == sh[i])
			i++;
		else
			return (0);
	}
	return (1);
}

int	main(int ac, char **av, char **env)
{
	t_assen	assen;
	int		i;

	i = 0;
	ac = 0;
	memset(&assen, 0, sizeof (assen));
	assen = minishell_init(env);
	while (env[i])
	{
		if (match_shlvl(env[i], "SHLVL=") == 0)
			env[i] = ft_strdup(env[i]);
		i += 1;
	}
	minishell(av, env, assen);
	return (*(g_global.status));
}
