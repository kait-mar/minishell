/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molabhai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 18:18:33 by molabhai          #+#    #+#             */
/*   Updated: 2020/12/26 14:19:30 by molabhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	 built_in(t_meta *meta, char *str, char **env, int status)
{
	int check;

	check = 0;
	if (meta->command == 1)
		cd_command(meta->argument, &status);
	else if (meta->command == 2)
		pwd_command(&status);
	else if (meta->command  == 3)
		env_command(env, meta, &status);
	else if (meta->command == 4)
		export_command(env, str, &status);
	else if (meta->command == 5)
		unset_command(env, str, &status);
	else if (meta->command == 6)
	{
	    printf("==> %s\n", meta->argument);
		echo(meta->argument, env, &status);
	}
	else
	{
		execut_command(env, meta->argument, &check);
		if (check == 1)
		{
			ft_printf("Command doesnt exist\n");
			status = 127;
		}
	}
}	

static	void	prompt(void)
{
	char	s[100];

	getcwd(s, 100);
	ft_printf("%s ", s);
}

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
	int		status;
	t_meta	*meta;
	t_meta	*head;

	status = 0;
	head = NULL;
	str = NULL;
	/*char **env;
	env = NULL;*/
	while (TRUE)
	{
		if (av[1])
			str = ft_strdup(av[1]);
		else
		{
			prompt();
			
			str = reading_input();
		}
		str = ft_strtrim(str, "\t");
		meta = split_it_all(str);
		head = meta;
        while (head != NULL)
        {
            if (head->meta == ';')
                built_in(head, str, env, status);
            else if (head->meta == '\0')
                built_in(head, str, env, status);
            head = head->next;
        }
		free_meta_struct(meta);
		if (av[1])
			exit(EXIT_SUCCESS);
	}
	return(0);
}