/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utility3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kait-mar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 15:19:11 by kait-mar          #+#    #+#             */
/*   Updated: 2021/04/15 15:19:13 by kait-mar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void 	cd_command(char *argument, int *status, char **env)
{
	char *s;
	int i;
	int k;
	static int first_time = 0;

    i = 0;
    k = 0;
	if (argument == NULL)
		return ;
	argument = take_only(argument);
	if (check_only_single_double(argument) == 0)
    {
        s = without_that(argument, '\"');
        s = without_that(argument, '\'');
        if (ft_strncmp(s, "", 1) == 0)
            s = ft_strdup("/Users/molabhai");
    }
	old_pwd(env);
	if (check_only_single_double(argument) == 0)
    {
		if (cd_command_helper(status, env, &s, first_time) == 0)
			return ;
    }
	cd_command_helper2(env, &first_time);
}

char    *take_only(char *s)
{
    int i;
    char *string;

    i = 0;
    if (s[i] == '\'')
    {
        i += 1;
        if (s[i] == '\'')
        {
            if (!(string = (char *) ft_calloc(sizeof (char ), i + 2)))
                return (NULL);
            i = 0;
            while (i < 2)
            {
                string[i] = s[i];
                i += 1;
            }
            string[i] = '\0';
        }
        else
        {
            while (s[i] != '\'' && s[i] != '\0')
                i += 1;
            if (!(string = (char *) ft_calloc(sizeof (char ), i + 2)))
                return (NULL);
            i = 0;
            string[i] = s[i];
            i += 1;
            while (s[i] != '\'' && s[i] != '\0')
            {
                string[i] = s[i];
                i += 1;
            }
            string[i] = s[i];
            string[i] = '\0';
        }
    }
    else if (s[i] == '\"')
    {
        i += 1;
        if (s[i] == '\"')
        {
            if (!(string = (char *) ft_calloc(sizeof (char ), i + 2)))
                return (NULL);
            i = 0;
            while (i < 2)
            {
                string[i] = s[i];
                i += 1;
            }
            string[i] = '\0';
        }
        else
        {
            while (s[i] != '\"' && s[i] != '\0')
                i += 1;
            if (!(string = (char *) ft_calloc(sizeof (char ), i + 2)))
                return (NULL);
            i = 0;
            string[i] = s[i];
            i += 1;
            while (s[i] != '\"' && s[i] != '\0')
            {
                string[i] = s[i];
                i += 1;
            }
            string[i] = s[i];
            string[i] = '\0';
        }
    }
    else
    {
        while (s[i] != ' ' && s[i] != '\t' && s[i] != '\0')
            i += 1;
        if (!(string = (char *) ft_calloc(sizeof (char ), i + 1)))
            return (NULL);
        i = 0;
        while (s[i] != ' ' && s[i] != '\t' && s[i] != '\0')
        {
            string[i] = s[i];
            i += 1;
        }
        string[i] = '\0';
    }
    return (string);
}

int	cd_command_helper(int *status, char **env, char **s, int first_time)
{	
	if (chdir(*s) < 0)
	{
		ft_printf("minishell: cd: %s: %s\n", *s, strerror(errno));
		if (first_time == 0)
			remove_old_pwd(env);
		free(*s);
		*s = NULL;
		*status = 1;
		return (0);
	}
	else
		*status = 0;
	free(*s);
	*s = NULL;
	return (1);
}

void	cd_command_helper2(char **env, int *first_time)
{
	char	*str;

	str = ft_calloc(sizeof(char), 100);
	if (str == NULL)
		return ;
	if (getcwd(str, 100) == NULL)
	    ft_printf("%s\n", strerror(errno));
	new_pwd(env, str);
	g_pwd_on = 0;
	g_global.check = 1;
    *first_time = 1;
}