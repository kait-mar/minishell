/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utility_support4.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molabhai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 14:46:55 by molabhai          #+#    #+#             */
/*   Updated: 2021/04/16 14:46:59 by molabhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	env_found(DIR *direct)
{
	struct dirent	*dirent;

	dirent = readdir(direct);
	while (dirent != NULL)
	{
		if (match(dirent->d_name, "env") == 1)
			return (1);
		dirent = readdir(direct);
	}
	return (0);
}

char	*right_path(char **path)
{
	int	i;
	DIR	*direct;

	i = 0;
	while (path[i])
	{
		direct = opendir(path[i]);
		if (direct == NULL)
			return (ft_strdup(""));
		if (env_found(direct) == 1)
			return (ft_strdup(path[i]));
		i += 1;
	}
	return (ft_strdup(""));
}

int	check_double_dot(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == ':')
			return (1);
		i += 1;
	}
	return (0);
}

char	*findin_env(char **env)
{
	int		i;
	char	*path;
	char	**paths;

	i = 0;
	while (env[i])
	{
		if (match("PATH", env[i]) == 1)
			path = only_after_equal(env[i]);
		i += 1;
	}
	if (check_double_dot(path) == 1)
		paths = ft_split(path, ':');
	else
	{
		paths = ft_calloc(sizeof(char), 2);
		if (!(paths))
			return (NULL);
		paths[0] = ft_strdup(path);
		paths[1] = NULL;
	}
	return (right_path(paths));
}

void	env_init(char **env)
{
	int		i;
	char	*s;
	int		pwd;
	int		shlvl;
	int		start;

	i = 0;
	pwd = 0;
	shlvl = 0;
	start = 0;
	s = ft_calloc(sizeof(char ), 100);
	if (!(s))
		return ;
	i = fill_env_init(env, &pwd, &shlvl, &start);
	if (pwd == 0)
		pwd_env(s, env, &i);
	if (shlvl == 0)
		shlvl_env(env, &i);
	if (start == 0)
		start_env(env, &i);
	free(s);
	s = NULL;
}
