/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executables_support.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molabhai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 17:23:15 by molabhai          #+#    #+#             */
/*   Updated: 2021/04/16 17:23:17 by molabhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	no_slash(char **splits)
{
	if (splits[0][0] == '"')
		splits[0] = ft_strtrim(splits[0], "\"");
	else if (splits[0][0] == '\'')
		splits[0] = ft_strtrim(splits[0], "'");
	ft_printf("minishell: %s: command not found\n", splits[0]);
	exit(127);
}

void	is_directory(char **splits)
{
	ft_printf("minishell: %s: is a directory\n", splits[0]);
	exit(126);
}

void	nothing(char **splits)
{
	ft_printf("minishell: %s: No such file or directory\n", splits[0]);
	exit(127);
}

int	exec_loop(char **commands, char **splits, char *path, char **env)
{
	int	i;

	i = 0;
	while (commands[i])
	{
		if (check_for_bin(splits[0]) == 0)
			commands[i] = ft_strjoin(commands[i], path);
		else if (check_for_bin(splits[0]) == 1)
			commands[i] = ft_strdup(splits[0]);
		if (execve(commands[i], splits, env) == -1)
			i += 1;
	}
	return (i);
}

void	exec_error(char **splits, char **commands, int i, char **env)
{
	if (errno == 13)
	{
		ft_printf("minishell: %s: %s\n", commands[i - 1], strerror(errno));
		exit(126);
	}
	execve(splits[0], splits, env);
	if (check_slash(splits[0]) == 0)
	{
		if (splits[0][0] == '"')
			splits[0] = ft_strtrim(splits[0], "\"");
		else if (splits[0][0] == '\'')
			splits[0] = ft_strtrim(splits[0], "'");
		ft_printf("minishell: %s: command not found\n", splits[0]);
		exit(127);
	}
}
