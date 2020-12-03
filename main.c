/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molabhai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 18:18:33 by molabhai          #+#    #+#             */
/*   Updated: 2020/12/03 18:44:40 by molabhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



int		check_wich_command(char *str)
{
	if (ft_strncmp(str, "cd", 2) == 0)
		return (1);
	return (0);
}

int		main(int ac, char **av, char **env)
{
	char *str;
	t_command_cd *cd;
	char **splits;
	pid_t  pid1;
	int		status;
	char	*pwd;
	int i;

	str = NULL;
	pwd = NULL;
	cd = malloc(sizeof(t_command_cd));
	if (cd == NULL)
		return (-1);
	while (1)
	{
		str = reading_input(str);
		str = ft_strtrim(str, "\t");
		splits = split_to_tokens(str);
		cd->command = splits[0];
		cd->argument = splits[1];
		if (check_wich_command(cd->command) == 1)
		{
			pwd = cd_command(cd->argument);
			printf("==> %s\n", pwd);
		}
	}
	return(0);
}
