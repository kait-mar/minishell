/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executables.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molabhai <molabhai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 17:25:32 by molabhai          #+#    #+#             */
/*   Updated: 2021/03/10 15:28:05 by molabhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*only_after_equal(char *str)
{
	int		i;
	char	*s;
	int		j;

	i = 0;
	j = 0;
	while (str[i] != '=')
		i += 1;
	if (str[i] == '=')
		i += 1;
	while (str[j] != '\0')
		j += 1;
	s = (char *) malloc(sizeof(char) * (j + 1));
	if (!(s))
		return (NULL);
	j = 0;
	while (str[i] != '\0')
	{
		s[j] = str[i];
		i += 1;
		j += 1;
	}
	s[j] = '\0';
	return (s);
}

int	check_for_bin(char *path)
{
	int		i;
	char	**check;

	i = 0;
	check = ft_split(path, '/');
	while (check[i] != NULL)
	{
		if (match(check[i], "bin") == 1)
			return (1);
		i += 1;
	}
	return (0);
}

int	check_prermission(char *string)
{
	struct stat	stats;

	if (stat(string, &stats) == -1)
	{
		ft_printf("minishell: %s: %s\n", string, strerror(errno));
		return (-1);
	}
	else
	{
		if (stats.st_mode & X_OK)
			return (1);
		else
			return (0);
	}
	return (0);
}

int	check_slash(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '/')
			return (1);
		i += 1;
	}
	return (0);
}

void	execut_command(char **env, char *str, int *statut)
{
	char	**splits;
	pid_t	pid;
	int		status;

	splits = NULL;
	pid = fork();
	if (pid < 0)
		exit(EXIT_FAILURE);
	else if (pid == 0)
		execution(splits, str, env);
	else
	{
		g_global.on = 1;
		waitpid(pid, &status, WUNTRACED);
		if (g_global.s_status == 0)
			*statut = WEXITSTATUS(status);
		g_global.s_status = 0;
		g_global.on = 0;
	}
}
