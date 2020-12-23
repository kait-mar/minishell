/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molabhai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 18:18:33 by molabhai          #+#    #+#             */
/*   Updated: 2020/12/23 18:09:31 by molabhai         ###   ########.fr       */
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
	if (check_unset(str) == 0)
		return (5);
	if (echo_strcmp(str, "echo") == 0)
		return (6);
	/* Here CHECK your command is lexically correct*/
	return (0);
}

//int		main()
int		main(int ac, char **av, char **env)
{
	char *str;
	t_command_cd *cd;
	char **splits;
	pid_t  pid1;
	int		status;
	char	*pwd;
	char s[100];
	int i;
	int check;
	t_meta	*meta;
	t_meta	*head;

	//char **av;
	//char **env;
	//env = malloc(2*sizeof(char *));
	//*env = "PATH=user/bin";
	//env[1] = NULL;
	status = 0;
	check = 0;
	str = NULL;
	pwd = NULL;
	cd = malloc(sizeof(t_command_cd));
	if (cd == NULL)
		return (-1);
	while (1)
	{
		if (!(av[1]))
		{
			getcwd(s, 100);
			ft_printf("%s ", s);
		}
		if (av[1])
			str = ft_strdup(av[1]);
		else
			str = reading_input(str);
		//str = "echo \"hello '$'\"";
		str = ft_strtrim(str, "\t");
		splits = split_to_tokens(str);
		i = how_mutch_argument(str, 0);
		if (i > 0)
		{
			meta = split_it_all(str);
			head = meta;
			while (head != NULL)
			{
				printf("==> %d || ==> %s || ==> %c\n", head->command, head->argument, head->meta);
				head = head->next;
			}
			i = how_mutch_argument(str, 2);
			splits[0] = ft_strtrim(splits[0], "\t");
			if (i == 1)
				splits[1] = ft_strtrim(splits[1], "\t");
			else if (i == 0 && (check_wich_command(str) == 1))
				splits[1] = ft_strdup("/Users/molabhai");
			if (check_wich_command(splits[0]) == 1)
				cd_command(splits[1], i, &status);
			else if (check_wich_command(splits[0]) == 2)
				pwd_command(&status);
			else if (check_wich_command(splits[0]) == 3)
				env_command(env, splits, &status);
			else if (check_wich_command(splits[0]) == 4)
				export_command(env, str, &status);
			else if (check_wich_command(splits[0]) == 5)
				unset_command(env, str, &status);
			else if (check_wich_command(splits[0]) == 6)
			{
				//check the case of ech"o"
				//case of PATH and path
				//case of *
				//echo """"hello""""
				echo(str, env, &status);
				//return (0);
			}
			else
			{
				execut_command(env, str, &check);
				if (check == 1)
				{
					ft_printf("Command [%s] doesnt exist\n", splits[0]);
					status = 127;
				}
			}
		}
		if (av[1])
			exit(EXIT_SUCCESS);
	}
	return(0);
}
