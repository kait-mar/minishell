/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molabhai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 11:21:15 by molabhai          #+#    #+#             */
/*   Updated: 2021/04/09 11:22:02 by molabhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_assen	minishell_init(char **env)
{
	t_assen	assen;

	memset(&g_global, 0, sizeof(g_global));
	memset(&assen, 0, sizeof(t_assen));
	g_global.status = malloc(sizeof(int ));
	*(g_global.status) = 0;
	filling_export(env);
	filling(&assen);
	return (assen);
}

t_meta	*minishell_exec_helper(t_meta *head, char **env)
{
	char	*s;

	head->argument = chang_dollar_sign(head->argument, env);
	if (head->command == 0)
	{
		s = take_first_word(head->argument);
		head->command = check_wich_command(s);
		free(s);
	}
	return (head);
}

void	minishell_execution(t_meta *head, t_assen assen, char **env)
{
	while (head != NULL)
	{
		head = minishell_exec_helper(head, env);
		if (token_error(head, g_global.status) == 1)
			break ;
		if (head->meta == ';')
			built_in(head, assen, env);
		else if (head->meta == '|')
			head = pipe_file(head, assen, env, g_global.status);
		else if (head->meta_append == 1)
		{
			head = redirect_output(head, assen, env, g_global.status);
			if (ft_strcmp(head->argument, "") == 0 && head->meta == '|')
				head = head->next;
		}
		else if (head->meta == '>')
			head = redirect_output(head, assen, env, g_global.status);
		else if (head->meta == '<')
			head = redirect_intput(head, assen, env, g_global.status);
		else if (head->meta == '\0')
			built_in(head, assen, env);
		if (head != NULL && head->meta != '|')
			head = head->next;
	}
}

t_meta	*minishell_helper(t_meta *meta, char **env, char **str, t_meta *global)
{
	char	*str_free;

	str_free = *str;
	*str = remove_space(*str);
	free(str_free);
	str_free = *str;
	*str = ft_strtrim(*str, "\t");
	free(str_free);
	str_free = *str;
	*str = escape_normal(*str);
	free(str_free);
	free_head(meta);
	meta = NULL;
	meta = split_it_all(*str, env, global);
	return (meta);
}

void	minishell(char **av, char **env, t_assen assen)
{
	t_meta		*meta;
	t_meta		*head;
	t_meta		*global;
	char		*str;
	char		*string;
	t_history	history;

	head = NULL;
	str = NULL;
	meta = NULL;
	string = malloc(BUFFER + 1);
	global = NULL;
	if (av[1] == NULL)
	{
		memset(&history, 0, sizeof(t_history));
		history = init_hist(history);
	}
	while (TRUE)
	{
		signal_handler(g_global.status);
		if (av[1])
			str = ft_strdup(av[1]);
		else
		{
			prompt();
			str = reading_input(&assen, string, history);
		}
		meta = minishell_helper(meta, env, &str, global);
		head = meta;
		minishell_global(head, assen, env, av);
	}
}
