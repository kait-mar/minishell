/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kait-mar <kait-mar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 18:18:33 by molabhai          #+#    #+#             */
/*   Updated: 2021/02/02 10:35:40 by kait-mar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static  char    *semi_split(char *str)
{
    int     i;
    char    *s;

    i = 0;
    while (str[i] != ';')
        i += 1;
    if (!(s = (char *) malloc((sizeof(char) * (i +1) ))))
        return (NULL);
    i = 0;
    while (str[i] != ';')
    {
        s[i] = str[i];
        i += 1;
    }
    s[i] = '\0';
    return (s);
}

void 	 built_in(t_meta *meta, char *str, char **env, int *status, int i)
{
	int check;
	int  exept;

	check = 0;
	exept = 0;
    if (meta->command == 1)
        cd_command(meta->argument, status, env);
	else if (meta->command == 2)
        pwd_command(status, exept);
	else if (meta->command  == 3)
		env_command(env, meta, status);
	else if (meta->command == 4)
        export_command(env, meta->argument, status, NULL);
	else if (meta->command == 5)
		unset_command(env, str, status);
	else if (meta->command == 6)
        echo(meta->argument, env, status);
	else if (meta->command == 0)
	{
	    if (ft_strcmp(meta->argument, "") != 0)
	    {
            g_process = 1;
            execut_command(env, meta->argument, &check, i);
        }
		if (check == 1)
		{
			ft_printf("minishell: %s: command not found\n", meta->argument);
			g_process = 0;
			*status = 127;
		}
	}
    if (meta->command == 7)
        exit_command(*status, meta->argument);
}

void	prompt(int in)
{
	char	s[100];

	getcwd(s, 100);
	if (in == 1)
    {
        ft_printf("\n%s ", s);
        return ;
    }
	else if (in == 0)
        ft_printf("%s ", s);
}

int		check_wich_command(char *str)
{
    int exept;

    exept = 0;
	if (ft_strncmp(str, "cd", 2) == 0 && (ft_isalpha(str[2]) == 0))
		return (1);
	if (check_pwd(str, &exept) == 0)
		return (2);
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

int    seach_for(char *s)
{
    int i;

    i = 0 ;
    while (s[i] != '\0')
    {
        if (s[i] == '\\')
            return (1);
        i += 1;
    }
    return (0);
}
/*
int		main(int ac, char **av, char **env)
{
	char *str;
	char    *tmp;
	int		status;
	t_meta	*meta;
	t_meta	*head;
	t_semi  *semi;
	int     on;

	status = 0;
	g_on = 0;
	g_in_signal = 0;
	g_first_time = 0;
	g_in_line = 0;
	g_check_single_quote = 0;
    g_check_double_quote = 0;
	on = 0;
	head = NULL;
	str = NULL;
	g_export = NULL;
    if (!(g_old_pwd = (char *) ft_calloc(sizeof (char ), 100)))
        return -1;
	filling_export(env);
	tmp = NULL;
	while (TRUE)
	{
        signal_handler(&status);
        if (av[1])
			str = ft_strdup(av[1]);
		else
		{
			prompt(g_in_signal);
			str = reading_input();
		}
        str = ft_strtrim(str, "\t");
        meta = split_it_all(str);
		head = meta;
        while (head != NULL)
        {
            head->argument = chang_dollar_sign(head->argument, env);
            if (head->meta == ';')
            {
                tmp = semi_split(str);
                built_in(head, tmp, env, &status, 0);
                str = split_to_last_cmd(str);
            }
            else if (head->meta == '|')
                head = pipe_file(head, str, env, &status);
            else if (head->meta_append == 1)
                head = append_file(head, str, env, &status);
            else if (head->meta == '>')
                head = redirect_output(head, str, env, &status);
			 else if (head->meta == '<')
                head = redirect_intput(head, str, env, &status);
            else if (head->meta == '\0')
                built_in(head, str, env, &status, 0);
            if (head != NULL)
                head = head->next;
        }
        if (av[1])
            exit(status);
        on = 0;
        g_first_time = 1;
        g_in_signal = 0;
	}
	return(status);
}*/

int			main()
{
	char *str;
	char    *tmp;
	int		status;
	t_meta	*meta;
	t_meta	*head;
	t_semi  *semi;
	int     on;


	char **av;
	char **env;
	env = malloc(2*sizeof(char *));
	*env = "PATH=user/bin";
	env[1] = NULL;




	status = 0;
	g_on = 0;
	g_in_signal = 0;
	g_first_time = 0;
	g_in_line = 0;
	on = 0;
	head = NULL;
	str = NULL;
	g_export = NULL;
    if (!(g_old_pwd = (char *) ft_calloc(sizeof (char ), 100)))
        return -1;
	filling_export(env);
	tmp = NULL;
	while (TRUE)
	{
        signal_handler(&status);
       // if (av[1])
		//	str = ft_strdup(av[1]);
		//else
	//	{
			prompt(g_in_signal);
			//str = reading_input();
			str = "echo \"he | \"";
		//}
        str = ft_strtrim(str, "\t");
        meta = split_it_all(str);
		head = meta;
        while (head != NULL)
        {
            head->argument = chang_dollar_sign(head->argument, env);
            if (head->meta == ';')
            {
                tmp = semi_split(str);
                built_in(head, tmp, env, &status, 0);
                str = split_to_last_cmd(str);
            }
            else if (head->meta == '|')
                head = pipe_file(head, str, env, &status);
            else if (head->meta_append == 1)
                head = append_file(head, str, env, &status);
            else if (head->meta == '>')
                head = redirect_output(head, str, env, &status);
			 else if (head->meta == '<')
                head = redirect_intput(head, str, env, &status);
            else if (head->meta == '\0')
                built_in(head, str, env, &status, 0);
            if (head != NULL)
                head = head->next;
        }
        if (av[1])
            exit(status);
        on = 0;
        g_first_time = 1;
        g_in_signal = 0;
	}
	return(status);
}