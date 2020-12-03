/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molabhai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 17:46:24 by molabhai          #+#    #+#             */
/*   Updated: 2020/12/01 20:47:31 by molabhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <dirent.h>

static char     *reading_input(char *str)
{
	get_next_line(1, &str);
	return (str);
}

static char 		**checking(char **splits, int *check)
{
	int i;

	i = 0;
	*check = 0;
	while (splits[i])
	{
		if (strncmp(splits[i], "cd", 2) == 0)
		{
			*check += 1;
		}
		else if (i == 1)
				*check += 1;
		i += 1;
	}
	return (splits);
}

static char		**split_to_tokens(char *str)
{
	char	**splits;
	int		check;

//	cd = malloc(sizeof(char) * (sizeof(t_command_cd)));
	splits = ft_split(str, ' ');
	splits = checking(splits, &check);
	if (check != 2)
		return (NULL);
//	printf("==> %s\n", cd->token);
	return (splits);
}
		
static char 	**taking_command(char *str)
{
	char **splits;

	str = reading_input(str);
	if ((splits = split_to_tokens(str)) == NULL)
		return (NULL);
	
	return (splits);
}

void	cd_command(void)
{
	t_command_cd *cd;
	char *str;
	char **splits;
	pid_t pid1;
	int 	status;

	status = 0;
	if ((pid1 = fork()) < 0)
	{
		ft_putstr("Error to create a Child Process\n");
		return ;
	}
	if (pid1 == 0)
	{
		str = NULL;
		cd = (t_command_cd *) malloc(sizeof(char) * sizeof(t_command_cd));
		if ((splits = taking_command(str)) == NULL)
		{
			ft_putstr("Error in cd Command\n");
			return ;
		}
		cd->command = splits[0];
		cd->argument = splits[1];
		printf("command == > %s || argument == > %s\n", cd->command, cd->argument);
		chdir(cd->argument);
		system("pwd");
		exit(status);
	}
	else {
		wait(&status);
	}
}



