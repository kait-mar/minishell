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
		execve(splits[0], splits, NULL);
		ft_printf("minishell: %s: No such file or directory\n", splits[0]);
		exit(127);
	}
	commands = ft_split(path, ':');
	exec_exec(splits, commands, env);
}

char	*first_return(char *bult, char **string)
{
	char	*t;
	int		j;

	t = malloc(2);
	j = how_many_escape(bult);
	if (j % 2 != 0)
	{
		while (*(bult + 1) == '\\')
			(bult)++;
	}
	else
	{
		while (*bult == '\\')
			(bult)++;
	}
	j /= 2;
	while (--j >= 0)
	{
		*t = '\\';
		t[1] = '\0';
		*string = ft_strjoin(*string, t);
	}
	return (bult);
}

char	*second_return(char *bult, char **string)
{
	char	*t;

	t = malloc(2);
	bult++;
	*t = *(bult++);
	t[1] = '\0';
	*string = ft_strjoin(*string, t);
	return (bult);
}

char	*third_return(char *bult, char **string)
{
	char	*t;

	t = malloc(2);
	*t = *(bult++);
	t[1] = '\0';
	*string = ft_strjoin(*string, t);
	return (bult);
}

char	*forth_return(char *bult, char **string)
{
	char	*t;

	t = malloc(2);
	*t = *(bult++);
	t[1] = '\0';
	*string = ft_strjoin(*string, t);
	return (bult);
}
