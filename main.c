/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kait-mar <kait-mar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 18:18:33 by molabhai          #+#    #+#             */
/*   Updated: 2021/01/05 10:04:09 by kait-mar         ###   ########.fr       */
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

t_pipe 	 *built_in(t_meta *meta, char *str, char **env, int *status)
{
	int check;
	int  exept;
	t_pipe *ret;

	check = 0;
	exept = 0;
    if (!(ret = (t_pipe *) malloc(sizeof (t_pipe))))
        return (NULL);
	if (meta->command == 1)
        ret->s_pipe = cd_command(meta->argument, status, g_piping);
	else if (check_pwd(str, &exept) == 0)
    {
	    ret->command = 2;
        ret->s_pipe= pwd_command(status, exept, g_piping);
    }
	else if (meta->command  == 3)
		ret->c_pipe = env_command(env, meta, status, g_piping);
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
			*status = 127;
		}
	}
    if (meta->command == 7)
        exit_command(*status, meta->argument);
    ret->command = meta->command;
    return (ret);
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
	char    *tmp;
	int		status;
	t_meta	*meta;
	t_meta	*head;

	g_piping = 0;
	status = 0;
	head = NULL;
	str = NULL;

	/*char **av;
	char **env;
	env = malloc(2*sizeof(char *));
	*env = "PATH=user/bin";
	env[1] = NULL;*/

	tmp = NULL;
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
            {
                tmp = semi_split(str);
                built_in(head, tmp, env, &status);
            }
            else if (head->meta == '|')
            {
                printf("Here\n");
                head = pipe_file(meta,str, env, &status);
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
            g_piping = 0;
        }
        if (av[1])
            exit(EXIT_SUCCESS);
	}
	return(0);
}