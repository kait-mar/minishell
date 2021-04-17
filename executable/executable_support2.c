/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executable_support2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molabhai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 13:45:42 by molabhai          #+#    #+#             */
/*   Updated: 2021/04/17 13:45:44 by molabhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void 	exec_errno2(char **splits)
{
	ft_printf("minishell: %s: %s\n", splits[0], strerror(errno));
	exit(127);
}

void	no_permissiom(char **splits)
{
	ft_printf("minishell: %s: Permission denied\n", splits[0]);
	exit(126);
}

void	exec_exec(char **splits, char **commands, char **env)
{
	char		*path;
	int			i;
	struct stat	stats;

	i = 0;
	path = ft_strjoin("/", splits[0]);
	stat(splits[0], &stats);
	if (check_slash(splits[0]) == 0 && S_ISDIR(stats.st_mode))
		no_slash(splits);
	if (S_ISDIR(stats.st_mode))
		is_directory(splits);
	if (commands[i] == NULL)
		nothing(splits);
	i = exec_loop(commands, splits, path, env);
	exec_error(splits, commands, i, env);
	if (errno == 2)
		exec_errno2(splits);
	else if (((S_IRUSR & stats.st_mode) && (S_IXUSR & stats.st_mode))
		 || ((S_IRUSR & stats.st_mode)
			&& (S_IXUSR & stats.st_mode) && (S_IWUSR & stats.st_mode)))
		exit(0);
	else
		no_permissiom(splits);
}

char	*return_parse(char **splits, char **env)
{
	char	*print;
	char	**changes;
	char	*return_parsing;

	print = ft_strdup(splits[1]);
	changes = keep_split(print, 39, 34);
	return_parsing = return_parsed(changes, env);
	splits[1] = ft_strdup(return_parsing);
	return (splits[1]);
}

char	*filling_path(char **env, int *on)
{
	char	*path;
	int		i;

	i = 0;
	while (env[i])
	{
		if (in_match(only_before_equal(env[i]), "PATH") == 1)
		{
			path = only_after_equal(env[i]);
			*on = 1;
		}
		i += 1;
	}
	return (path);
}
