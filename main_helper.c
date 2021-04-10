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

#include "minishell.h"



t_assen    minishell_init(char **env)
{
    t_assen assen;

    memset(&g_global, 0, sizeof (g_global));
    memset(&assen, 0, sizeof (t_assen));
    g_global.status = malloc(sizeof (int ));
    *(g_global.status) = 0;
    if (!(g_global.old_pwd = (char *) ft_calloc(sizeof (char ), 100)))
        return (assen);
    filling_export(env);
    filling(&assen);
    return (assen);
}

void minishell_execution(t_meta *head, t_assen assen, char **env)
{
	while (head != NULL)
    {
        head->argument = chang_dollar_sign(head->argument, env);
        if (head->command == 0)
            head->command = check_wich_command(take_first_word(head->argument));
        if (token_error(head, g_global.status) == 1)
            break;
        if (head->meta == ';') {
            built_in(head, assen, env, g_global.status);
        } else if (head->meta == '|')
            head = pipe_file(head, assen, env, g_global.status);
        else if (head->meta_append == 1) {
            head = redirect_output(head, assen, env, g_global.status);
            if (ft_strcmp(head->argument, "") == 0 && head->meta == '|')
                head = head->next;
        } else if (head->meta == '>') {
            head = redirect_output(head, assen, env, g_global.status);
            if (ft_strcmp(head->argument, "") == 0 && head->meta == '|')
                head = head->next;
        } else if (head->meta == '<')
            head = redirect_intput(head, assen, env, g_global.status);
        else if (head->meta == '\0')
            built_in(head, assen, env, g_global.status);
        if (head != NULL)
            head = head->next;
    }
}

void    minishell(char **av, char **env, t_assen assen)
{
    t_meta	*meta;
    t_meta	*head;
    char    *str;

    head = NULL;
    str = NULL;
    meta = NULL;
    while (TRUE)
    {
        signal_handler(g_global.status);
        if (av[2])
            str = ft_strdup(av[2]);
        else
        {
            prompt(g_global.in_signal);
            str = reading_input(&assen);
        }
		str = remove_space(str);
        str = ft_strtrim(str, "\t");
        str = escape_normal(str);
        meta = split_it_all(str, env);
        head = meta;
        minishell_execution(head, assen, env);
        if (av[2])
            exit(*(g_global.status));
        g_global.first_time = 1;
        if (g_in_redirect == 1)
        {
            g_in_redirect = 0;
            g_global.in_signal = 1;
        }
        else
            g_global.in_signal = 0;
        free(str);
        str = NULL;
    }
}