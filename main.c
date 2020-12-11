/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molabhai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 18:18:33 by molabhai          #+#    #+#             */
/*   Updated: 2020/12/07 14:35:33 by molabhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_wich_command(char *str)
{
	if (ft_strncmp(str, "cd", 2) == 0 && (ft_isalpha(str[2]) == 0))
		return (1);
	 if (check_pwd(str) == 0)
		return (2);
	if (check_env(str) == 0)
		return (3);
	if (ft_strncmp(str, "export", 6) == 0 && (ft_isalpha(str[6]) == 0))
		return (4);
	if (echo_strcmp(str, "echo") == 0)
		return (5);
	/* Here CHECK your command is lexically correct*/
	return (0);
}

int		main()
//int		main(int ac, char **av, char **env)
{
	char *str;
	t_command_cd *cd;
	char **splits;
	pid_t  pid1;
	int		status;
	char	*pwd;
	int i;


	char **av;
	char **env;
	env = malloc(2*sizeof(char *));
	*env = "PATH=user/bin";
	env[1] = NULL;
	str = NULL;
	pwd = NULL;
	cd = malloc(sizeof(t_command_cd));
	if (cd == NULL)
		return (-1);
	while (1)
	{
		//str = reading_input(str);
		str = "echo $path hello ";
		str = ft_strtrim(str, "\t");
		splits = split_to_tokens(str);
		i = how_mutch_argument(str, 0);
		if (i > 0)
		{
			i = how_mutch_argument(str, 2);
			splits[0] = ft_strtrim(splits[0], "\t");
			if (i == 1)
				splits[1] = ft_strtrim(splits[1], "\t");
			else if (i == 0 && (check_wich_command(str) == 1))
				splits[1] = ft_strdup("/Users/molabhai");
			if (check_wich_command(splits[0]) == 1)
				cd_command(splits[1], i);
			else if (check_wich_command(splits[0]) == 2)
				pwd_command();
			else if (check_wich_command(splits[0]) == 3)
				env_command(env, splits);
			else if (check_wich_command(splits[0]) == 4)
				export_command(env, splits);
			else if (check_wich_command(splits[0]) == 5)
			{
				//check the case of ech"o"
				echo(str, env);
			}
			else
				ft_printf("Command [%s] doesnt exist\n", splits[0]);
		}
	}
	return(0);
}
