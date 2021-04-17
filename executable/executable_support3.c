/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executable_support3.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molabhai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 14:15:10 by molabhai          #+#    #+#             */
/*   Updated: 2021/04/17 14:15:12 by molabhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execution(char **splits, char *str, char **env)
{
	char	*path;
	int		on;
	char	**commands;

	on = 0;
	splits = take_only_carac(str);
	if (check_wich_command(splits[0]) != 0)
		splits[0] = ft_strdup(str);
	else if (check_wich_command(splits[0]) == 0 && splits[1] != NULL)
		splits[1] = return_parse(splits, env);
	path = filling_path(env, &on);
	if (on == 0)
	{
		ft_printf("minishell: %s: No such file or directory\n", splits[0]);
		exit(127);
	}
	commands = ft_split(path, ':');
	free(path);
	exec_exec(splits, commands, env);
}
