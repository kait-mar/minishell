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

int     check_slash(char *s)
{
    int i;

    i = 0;
    while (s[i] != '\0')
    {
        if (s[i] == '/')
            return (1);
        i += 1;
    }
    return (0);
}
void	execut_command(char **env, char *str, int *check,  int *statut)
{
	char **splits;
	char *path;
	char **commands;
	char *print;
	char *new_argument;
	char **changes;
	char *return_parsing;
	int 	i;
	pid_t	pid;
	int     fd;
	int status;
    struct stat stats;
    int on;

	i = 0;
	on = 0;
    if ((pid = fork()) < 0)
    {
        ft_printf("Failure\n");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        splits = take_only_carac(str);
        if (check_wich_command(splits[0]) != 0)
            splits[0] = ft_strdup(str);
        else if (check_wich_command(splits[0]) == 0 && splits[1] != NULL)
        {
            print = ft_strdup(splits[1]);
            //new_argument = take_first_word_re(splits[i]);
            changes = keep_split(print, 39, 34);
            return_parsing = return_parsed(changes, env);
            splits[1] = ft_strdup(return_parsing); // ft_strjoin_re(new_argument, return_parsing);
        }
        while (env[i])
        {
            if (in_match(only_before_equal(env[i]), "PATH") == 1)
            {
                path = only_after_equal(env[i]);
                on = 1;
            }
            i += 1;
        }
        if (on == 0)
        {
            ft_printf("minishell: %s: No such file or directory\n", splits[0]);
            exit(127);
        }
        commands = ft_split(path, ':');
        free(path);
        path = ft_strjoin("/", splits[0]);
        i = 0;
        *check = 2;
        stat(splits[0], &stats);
        if (check_slash(splits[0]) == 0 && S_ISDIR(stats.st_mode))
        {
            if (splits[0][0] == '"')
                splits[0] = ft_strtrim(splits[0], "\"");
            else if (splits[0][0] == '\'')
                splits[0] = ft_strtrim(splits[0], "'");
            ft_printf("minishell: %s: command not found\n", splits[0]);
            exit(127);
        }
        if (S_ISDIR(stats.st_mode))
        {
            ft_printf("minishell: %s: is a directory\n", splits[0]);
            exit(126);
        }
        if (commands[i] == NULL)
        {
            ft_printf("minishell: %s: No such file or directory\n",splits[0]);
            exit(127);
        }
        while (commands[i])
        {
            if (check_for_bin(splits[0]) == 0)
                commands[i] = ft_strjoin(commands[i], path);
            else if (check_for_bin(splits[0]) == 1)
                commands[i] = ft_strdup(splits[0]);
            if (execve(commands[i], splits, env) == -1)
                i += 1;
        }
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
            //ft_printf("minishell: %s: command not found\n", without_that(splits[0], '\''));
            ft_printf("minishell: %s: command not found\n", splits[0]);
            exit(127);
        }
        if (errno == 2)
        {
            ft_printf("minishell: %s: %s\n", splits[0], strerror(errno));
            exit(127);
        }
        else if (((S_IRUSR & stats.st_mode) && (S_IXUSR & stats.st_mode))
                 || ((S_IRUSR & stats.st_mode) && (S_IXUSR & stats.st_mode) && (S_IWUSR & stats.st_mode)))
            exit(0);
        else
        {
            ft_printf("minishell: %s: Permission denied\n", splits[0]);
            exit(126);
        }
    }
    else
    {
        g_pid = pid;
        g_on = 1;
        waitpid(pid, &status, WUNTRACED);
        *statut = WEXITSTATUS(status);
        g_on = 0;
    }
    // }
}