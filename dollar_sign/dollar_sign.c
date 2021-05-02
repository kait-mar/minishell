/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_sign.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molabhai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 16:27:14 by molabhai          #+#    #+#             */
/*   Updated: 2021/02/18 16:27:16 by molabhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char    *chang_dollar(char *s, char **env, int *on)
{
    int i;
    int escape;
    char *string;
    char *ss;
    char *string_free;

    i = 0;
    escape = count_escap(s);
    ss = take_away_dollar(s);
    string = NULL;
    if (ft_strcmp(ss, "PWD") == 0 && g_global.pwd_on == 0)
    {
        string = ft_strdup(g_global.pwd_only);
        string = take_after_equal(string);
        *on = 1;
    }
	else if (ft_strcmp(ss, "OLDPWD") == 0 && g_global.oldpwd_on == 0)
    {
        if (g_global.check == 0)
            string = ft_strdup("");
        else
        {
            string = ft_strdup(g_global.oldpwd_only);
            string = take_after_equal(string);
            *on = 1;
        }
    }
    else
    {
        while (env[i] != NULL)
        {
            if (match(env[i], ss) == 1)
            {
                string = ft_strdup(env[i]);
                string = take_after_equal(string);
                *on = 1;
            }
            i += 1;
        }

    }
    if (*on == 0)
    {
    	if (string)
    		free(string);
        string = ft_strdup("");
        *on = 2;
    }
    if (escape > 0)
    {
        if (*on == 1)
		{
        	string_free = string;
			string = adding_escape(string, escape);
			free(string_free);
		}
        else
            string = adding_escape(ss, escape);
    }
    free(ss);
    free(s);
    return (string);
}



char    *chang_dollar_sign(char *str, char **env)
{
    t_sign  lst;

    lst.i = 0;
    lst.error = 0;
    lst.on = 0;
    lst.remove = 0;
    lst.space_front = 0;
    lst.s = NULL;
    lst.space_back = 0;
    while (str[lst.i] != '\0')
    {
        if (str[lst.i] == '\'')
        {
            lst.i += 1;
            while (str[lst.i] !='\'' && str[lst.i] !='\0')
                lst.i += 1;
            if (str[lst.i] == '\'')
                lst.i += 1;
        }
        lst = change_dollar_core(lst, &str, env);
    }
    return (str);
}