/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kait-mar <kait-mar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 17:46:24 by molabhai          #+#    #+#             */
/*   Updated: 2021/01/19 15:28:07 by kait-mar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <dirent.h>
#include <errno.h>

/*
int		search(char *str)
{
    int i;

    i = 0;
    while (str[i] != '\0')
    {
        if (str[i] == '\n')
        {
            str[i] = '\0';
            return (TRUE);
        }
        i++;
    }
    return (FALSE);
}*/

t_assen    *reading_input(t_assen *assen, char **cmd)
{
	char	*str;
	char    *tmp;
	t_history history;
	int fd;
	char *clear;
	struct termios tp;
	struct termios save;


    str = NULL;
    tmp = NULL;
	//i = 0;
	//k = 0;
	//check = 0;
	/*while (i == 0)
	{
	    if (k == 0 ||  (g_in_line == 0 && i == 0))
        {
            i = get_next_line(1, &str);
            if (k == 0)
                s = ft_strdup(str);
            if (g_in_line == 1 && i == 1)
            {
                g_in_line = 0;
                return (s);
            }
        }
        if (ft_strcmp(str, "") == 0 && i == 0 && check == 0)
        {
            ft_printf("exit\n");
            exit(EXIT_SUCCESS);
        }
        else if (i == 0 && ft_strcmp(str, "") != 0 && k == 0)
            check = 1;
        k += 1;
    }*/
    ft_memset(&history, 0, sizeof (t_history));
    if (!(str = (char *) ft_calloc(1, BUFFER)))
        return (NULL);
	history = init_hist(history);
	//printf("histort.tty_name ==> %s\n", history.tty_name);
    fd = open(history.tty_name, O_RDWR | O_NOCTTY);
    if (isatty(fd))
    {
        if (tcgetattr(fd, &tp) == -1)
            exit(-1);
        save = tp;
        tp.c_lflag &= ~(ICANON);
        tp.c_cc[VMIN] = 0;
        tp.c_cc[VTIME] = 0;
        if (tcsetattr(fd, TCSANOW, &tp) == 1)
            exit (-1);
        while (TRUE)
        {
            read(fd, str, BUFFER);
            if (memcmp(str, history.up_arrow, 3) == 0)
            {
                tputs(history.clear, 0, int_put);
                if (assen->prev != NULL)
                    assen = assen->prev;
                printf("%s\n", assen->cmd);
               // break ;
            }
            else if (memcmp(str, history.down_arrow, 3) == 0)
            {
                tputs(history.clear, 0, int_put);
                if (assen->next != NULL)
                    assen = assen->next;
                printf("%s\n", assen->cmd);
               // break ;
            }
            tmp = extend(str, tmp);
            if (!(str = (char *) ft_calloc(1, BUFFER)))
                return (NULL);
            if (search(tmp))
            {
                append_assen(&assen, tmp);
                break ;
            }
        }
        //get_next_line(0, &str);
        if (tcsetattr(fd, TCSANOW, &save) == 1)
            exit (-1);
    }
    *cmd = ft_strdup(tmp);
	return (assen);
}

char		**split_to_tokens(char *str)
{
	char	**splits;
	int		check;

	splits = ft_split(str, ' ');
	return (splits);
}

/*
char 	**taking_command(char *str)
{
	char **splits;

	str = reading_input(str);
	if ((splits = split_to_tokens(str)) == NULL)
		return (NULL);
	
	return (splits);
}*/


char    *add_in(char *first, char *second)
{
    int i;
    int j;
    char *s;
    int len;

    len = ft_strlen(first);
    len += ft_strlen(second);
    i = 0;
    j = 0;
    if (!(s = (char *) ft_calloc(sizeof (char), len + 1)))
        return (NULL);
    while (first[i] != '\0')
    {
        s[i] = first[i];
        i += 1;
    }
    while (second[j] != '\0')
    {
        s[i] = second[j];
        j += 1;
        i += 1;
    }
    return (s);
}

int     find_old_pwd(char *s)
{
    if (ft_strncmp(s, "OLDPWD", 6) == 0)
        return (1);
    return (0);
}

int     find_pwd(char *s)
{
    if (ft_strncmp(s, "PWD", 3) == 0)
        return (1);
    return (0);
}

void    old_pwd(char **env)
{
    char *old_pwd;
    char *take_it;
    int i;
    int j;
    int k;

    i = 0;
    k = 0;
    j = 0;
    while (env[j])
    {
        if (find_pwd(env[j]) == 1)
        {
            take_it = only_after_equal(ft_strdup(env[j]));
            i = 1;
            break ;
        }
        j += 1;
    }
    if (i == 0 && g_pwd_on == 0)
    {
        if (getcwd(g_old_pwd, 100) == NULL)
            ft_printf("%s\n", strerror(errno));
        old_pwd = add_in("OLDPWD=", g_old_pwd);
    }
    else if (i == 1)
        old_pwd = add_in("OLDPWD=", take_it);
    else
        old_pwd = add_in("OLDPWD=", "");
    g_oldpwd_only = ft_strdup(old_pwd);
    while (env[i])
    {
        if (find_old_pwd(env[i]) == 1)
        {
            env[i] = ft_strdup(old_pwd);
            break ;
            k = 1;
        }
        i += 1;
    }
    if (env[i] == NULL && k == 0)
    {
        env[i] = ft_strdup(old_pwd);
        env[i + 1] = NULL;
        i += 1;
    }
}

void    new_pwd(char **env, char *str)
{
    int i;
    int k;
    char *old_pwd;

    i = 0;
    k = 0;
    old_pwd = add_in("PWD=", str);
    g_pwd_only = ft_strdup(old_pwd);
    while (env[i])
    {
        if (find_pwd(env[i]) == 1)
        {
            env[i] = ft_strdup(old_pwd);
            break ;
            k = 1;
        }
        i += 1;
    }
    if (env[i] == NULL && k == 0 && g_pwd_on == 0)
    {
        env[i] = ft_strdup(old_pwd);
        env[i + 1] = NULL;
        i += 1;
    }
}

void    remove_old_pwd(char **env)
{
    int i;
    char *string;
    char *s;

    i = 0;
    string = ft_strdup("OLDPWD");
    while (env[i])
    {
        if (match(env[i], string) == 1)
        {
            env[i] = NULL;
            break ;
        }
        i += 1;
    }
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

int     check_only_single_double(char *s)
{
    int i;

    i = 0;
    if (s[i] == '\'' && s[i + 1] == '\'')
        return (1);
    else if (s[i] == '\"' && s[i + 1] == '\"')
        return (1);
    return (0);
}

void 	cd_command(char *argument, int *status, char **env)
{
	char *str;
	char *s;
	int i;
	int k;
	static int first_time = 0;

    i = 0;
    k = 0;
	if (argument == NULL)
		return ;
	if (!(str = ft_calloc(sizeof(char), 100)))
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
        if (chdir(s) < 0)
        {
            ft_printf("minishell: cd: %s: %s\n", s, strerror(errno));
            if (first_time == 0)
                remove_old_pwd(env);
            free(s);
            s = NULL;
            *status = 1;
            return ;
        }
        else
            *status = 0;
        free(s);
        s = NULL;
    }
	if (getcwd(str, 100) == NULL)
	    ft_printf("%s\n", strerror(errno));
	new_pwd(env, str);
	g_pwd_on = 0;
	g_check = 1;
    first_time = 1;
}