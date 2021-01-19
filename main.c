/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kait-mar <kait-mar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 18:18:33 by molabhai          #+#    #+#             */
/*   Updated: 2021/01/17 15:48:41 by kait-mar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	 built_in(t_meta *meta, char *str, char **env, int *status)
{
	int check;
	int  exept;

	check = 0;
	exept = 0;
	if (meta->command == 1)
		cd_command(meta->argument, status);
	else if (check_pwd(str, &exept) == 0)
		pwd_command(status, exept);
	else if (meta->command  == 3)
		env_command(env, meta, status);
	else if (meta->command == 4)
		export_command(env, str, status);
	else if (meta->command == 5)
		unset_command(env, str, status);
	else if (meta->command == 6)
		echo(meta->argument, env, status);
	else if (meta->command == 0)
	{
		execut_command(env, meta->argument, &check);
		if (check == 1)
		{
			ft_printf("bash: %s: command not found\n", meta->argument);
			g_process = 0;
			*status = 127;
		}
	}
    if (meta->command == 7)
        exit_command(*status, meta->argument);
}

void	prompt(void)
{
	char	s[100];

	getcwd(s, 100);
	//printf(" entered to prompt\n");
	ft_printf("\n%s ", s);
	
}

int		check_wich_command(char *str)
{
	if (ft_strncmp(str, "cd", 2) == 0 && (ft_isalpha(str[2]) == 0))
		return (1);
	/*if (check_pwd(str) == 0)
		return (2);*/
	if (check_env(str) == 0)
		return (3);
	if (ft_strncmp(str, "export", 6) == 0 && (ft_isalpha(str[6]) == 0))
		return (4);
	if (check_unset(str) == 0)
		return (5);
	if (echo_strcmp(str, "echo") == 0)
		return (6);
	if (check_exit(str) == 1)
	    return (7);
	return (0);
}

//int			main()
int		main(int ac, char **av, char **env)
{
	char *str;
	int		status;
	t_meta	*meta;
	t_meta	*head;

	status = 0;
	head = NULL;
	str = NULL;
	/*char **av;
	char **env;
	env = malloc(2*sizeof(char *));
	*env = "PATH=user/bin";
	env[1] = NULL;*/
	while (TRUE)
	{
		g_process = 0;
		signal_handler(&status);
		//signal(SIGINT, inter_signal);
		if (av[1])
			str = ft_strdup(av[1]);
		else
		{
			prompt();
			str = reading_input();
		}
		//str = "echo hello kbjdcd skjdcs hsdcugd > kait";
		str = ft_strtrim(str, "\t");
		meta = split_it_all(str);
		head = meta;
        while (head != NULL)
        {
            if (head->meta == ';')
            {
                printf("Here\n");
                built_in(head, str, env, &status);
            }
            else if (head->meta_append == 1)
				head = append_file(head, str, env, &status);
            else if (head->meta == '>')
            {
                head = redirect_output(head, str, env, &status);
				//return (0);
				//printf("|%s|\n", head->argument);
            }
			 else if (head->meta == '<')
            {
                head = redirect_intput(head, str, env, &status);
            }
            else if (head->meta == '\0')
                built_in(head, str, env, &status);
            if (head != NULL)
                head = head->next;
        }
		if (av[1])
			exit(EXIT_SUCCESS);
		//else
     //       free_meta_struct(meta);
	}
	return(0);
}