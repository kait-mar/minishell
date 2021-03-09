/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executables.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kait-mar <kait-mar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 17:25:32 by molabhai          #+#    #+#             */
/*   Updated: 2021/02/02 10:14:32 by kait-mar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*only_after_equal(char *str)
{
	int i;
	char *s;
	int j;

	i = 0;
	j = 0;

	while (str[i] != '=')
		i += 1;
	if (str[i] == '=')
		i += 1;
	while (str[j] != '\0')
		j += 1;
	if (!(s = (char *) malloc(sizeof(char) * (j + 1))))
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

int     check_for_bin(char *path)
{
    int i;
    char **check;

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

int    check_prermission(char *string)
{
    struct stat stats;

    if (stat(string, &stats) == - 1)
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

void	execut_command(char **env, char *str, int *check, int j, int *statut)
{
	char **splits;
	char *path;
	char **commands;
	int 	i;
	pid_t	pid;
	int     fd;
	int status;

	i = 0;
	status = 0;
	if (j == 1)
    {
        splits = take_only_carac(str);
        while (env[i]) {
            if (in_match(only_before_equal(env[i]), "PATH") == 1)
                path = only_after_equal(env[i]);
            i += 1;
        }
        commands = ft_split(path, ':');
        free(path);
        path = ft_strjoin("/", splits[0]);
        i = 0;
        while (commands[i]) {
            commands[i] = ft_strjoin(commands[i], path);
            if (execve(commands[i], splits, env) == -1)
                i += 1;
        }
        *check = 1;
    }
	else
    {
        if ((pid = fork()) < 0)
        {
            ft_printf("Failure\n");
            exit(EXIT_FAILURE);
        }
        else if (pid == 0) {
            splits = take_only_carac(str);
            while (env[i])
            {
                if (in_match(only_before_equal(env[i]), "PATH") == 1)
                    path = only_after_equal(env[i]);
                i += 1;
            }
            commands = ft_split(path, ':');
            free(path);
            path = ft_strjoin("/", splits[0]);
            i = 0;
            *check = 2;
            while (commands[i])
            {
                if (check_for_bin(splits[0]) == 0)
                    commands[i] = ft_strjoin(commands[i], path);
                else if (check_for_bin(splits[0]) == 1)
                    commands[i] = ft_strdup(splits[0]);
                if (execve(commands[i], splits, env) == -1)
                    i += 1;
            }
           /* if (check_prermission(splits[0]) == -1)
                status = 127;
           else if (check_prermission(splits[0]) == 0)
                status = 126;
           else  if (check_prermission(splits[0]) == 1)
                execve(splits[0], splits, env);
           else
                status = 127;*/
           execve(splits[0], splits, env);
           exit(EXIT_FAILURE);
        }
        else
        {
            g_pid = pid;
            g_on = 1;
            waitpid(pid, &status, WUNTRACED);
            if (WIFEXITED(status))
           *statut = WEXITSTATUS(status);
            g_on = 0;
        }
    }
}