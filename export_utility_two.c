/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utility_two.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molabhai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 18:01:31 by molabhai          #+#    #+#             */
/*   Updated: 2020/12/12 18:47:00 by molabhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int     check_equal(char *s)
{
    int i;

    i = 0;
    while (s[i] != '\0')
    {
        if (s[i] == '=')
            return (1);
        i += 1;
    }
    return (0);
}

char    *adding_quote(char *s)
{
    char *s1;
    char *s2;
    int i;
    int j;
    char *str;

    i = 0;
    j = 0;

   if (check_equal(s) == 0)
       return (ft_strdup(s));
    while (s[i] != '=')
        i += 1;
    while (s[i] != '\0')
    {
        j += 1;
        i += 1;
    }
    if (!(s2 = (char *) ft_calloc(sizeof (char ), j + 3)))
        return (NULL);
    if (!(str = (char *) ft_calloc(sizeof(char ), j + i + 1)))
        return (NULL);
    s2[0] = '\"';
    j = 1;
    i = 0;
    while (s[i] != '=')
        i += 1;
    if (s[i] == '=')
        i += 1;
    while (s[i] != '\0')
    {
        s2[j] = s[i];
        i += 1;
        j += 1;
    }
    s2[j] = '\"';
    j += 1;
    s2[j] = '\0';
    i = 0;
    j = 0;
    while (s[i] != '=')
    {
        str[i] = s[i];
        i += 1;
    }
    str[i] = s[i];
    i += 1;
    while (s2[j] != '\0')
    {
        str[i] = s2[j];
        i += 1;
        j += 1;
    }
    str[i] = '\0';
    return (str);
}

char	*front_append(char *string, char *to_append)
{
	char *s;
	int i;
	int j;

	if (!(s = (char *) malloc(sizeof(char) * (ft_strlen(string) + ft_strlen(to_append) + 1))))
		return (NULL);
	i = 0;
	while (to_append[i] != '\0')
	{
		s[i] = to_append[i];
		i += 1;
	}
	j = 0;
	while (string[j] != '\0')
	{
		s[i] = string[j];
		i += 1;
		j += 1;
	}
	s[i] = '\0';
	s = adding_quote(s);
	return (s);
}

int		kait_count(char *str)
{
	int i;
	int	j;
	int k;
	int	count;

	i = 0;
	k = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (ft_isprint(str[i]))
		{
			j = i;
			while (((ft_isprint(str[j]) == 1 ) || str[j] == '=') &&
                    ((check_single_double_quote(str[j]) == 0)  || (check_single_double_quote(str[j]) == 1 && str[j - 1] == '\\') ))
				j += 1;
			count += 1;
			i = j;
		}
		if (check_double_quotes(str[i]) && str[i - 1] != '\\')
		{
			j = i + 1;
			while (check_double_quotes(str[j]) == 0)
				j += 1;
			count += 1;
		   i = j;
		}
		if (check_single_quotes(str[i]) && str[i - 1] != '\\')
		{
			j = i + 1;
			while (check_single_quotes(str[j]) == 0)
				j += 1;
			count += 1;
		   i = j;
		}
		if (str[i] != '\0')
			i += 1;
	}
	return (count);
}	

char    *append(char *s1, char *s2)
{
    char *str;
    int len;
    int i;
    int j;

    i = 0;
    j = 0;
    len = ft_strlen(s1) + ft_strlen(s2);
    if (!(str = (char *) ft_calloc(sizeof (char), len + 1)))
        return (NULL);
    while (s1[i] != '\0')
    {
        str[i] = s1[i];
        i += 1;
    }
    while (s2[j] != '\0')
    {
        str[i] = s2[j];
        i += 1;
        j += 1;
    }
    str[i] = '\0';
    return (str);
}

void    export_init(void)
{
    int i;
    char *s;
    char *string;
    int pwd;
    int shlvl;

    i = 0;
    pwd = 0;
    shlvl = 0;
    if (!(s = (char *) ft_calloc(sizeof(char ), 100)))
        return ;
    while (g_export->saver[i])
    {
        if (match("PWD", g_export->saver[i]) == 1)
            pwd = 1;
        else if (match("SHLVL", g_export->saver[i]) == 1)
            shlvl = 1;
        i += 1;
    }
    if (pwd == 0)
    {
        getcwd(s, 100);
        string = append("PWD=", s);
        g_export->saver[i] = ft_strdup(string);
        free(string);
        string = NULL;
        i += 1;
    }
    if (shlvl == 0)
    {
        string = append("SHLVL=", "1");
        g_export->saver[i] = ft_strdup(string);
        free(string);
        string = NULL;
        i += 1;
    }
}

int     env_found(DIR *direct)
{
    struct dirent *dirent;

    while ((dirent = readdir(direct)) != NULL)
    {
        if (match(dirent->d_name, "env") == 1)
            return (1);
    }
    return (0);
}

char    *right_path(char **path)
{
    int i;
    DIR *direct;

    i = 0;
    while (path[i])
    {
        direct = opendir(path[i]);
        if (env_found(direct) == 1)
            return (ft_strdup(path[i]));
        i += 1;
    }
    return (NULL);
}

char    *findin_env(char **env)
{
    int i;
    char *path;
    char **paths;

    i = 0;
    while (env[i])
    {
        if (match("PATH", env[i]) == 1)
            path = only_after_equal(env[i]);
        i += 1;
    }
    paths = ft_split(path, ':');
    return (right_path(paths));
}

void   env_init(char **env)
{
    int i;
    char *s;
    char *ss;
    char *string;
    int pwd;
    int shlvl;
    int start;

    i = 0;
    pwd = 0;
    shlvl = 0;
    start = 0;
    if (!(s = (char *) ft_calloc(sizeof(char ), 100)))
        return ;
    while (env[i])
    {
        if (match("PWD", env[i]) == 1)
            pwd = 1;
        else if (match("SHLVL", env[i]) == 1)
            shlvl = 1;
        else if ((match("_", env[i]) == 1))
            start = 1;
        i += 1;
    }
    if (pwd == 0)
    {
        getcwd(s, 100);
        string = append("PWD=", s);
        env[i] = ft_strdup(string);
        free(string);
        string = NULL;
        i += 1;
        env[i] = NULL;
    }
    if (shlvl == 0)
    {
        string = append("SHLVL=", "1");
        env[i] = ft_strdup(string);
        free(string);
        string = NULL;
        i += 1;
        env[i] = NULL;
    }
    if (start == 0)
    {
        ss = findin_env(env);
        string = append("_=", ss);
        string = ft_strjoin(string, "/env");
        env[i] = ft_strdup(string);
        free(string);
        string = NULL;
        i += 1;
        env[i] = NULL;
    }
}

void    filling_export(char **env)
{
    int i;
    int pwd;
    int shlvl;
    char *string;

    i = 0;
    pwd = 0;
    shlvl = 0;
    if (!(g_export = (t_export *) malloc(sizeof (t_export))))
        return ;
    if (!(g_export->saver = (char **) ft_calloc(sizeof (char *), arguments_in(env, i) + 3)))
        return ;
    while (env[i])
    {
        g_export->saver[i] = ft_strdup(env[i]);
        i += 1;
    }
    export_init();
    env_init(env);
}

int     in_it(char *s)
{
    int i;

    i = 0;
    while (s[i] != '\0')
    {
        if (s[i] == '=')
        {
            if (s[i] == '\'')
                i += 1;
            while (s[i] != '\0' &&  s[i] != '\'')
            {
                if (s[i] == '\"' || s[i] == '\\' || s[i] == '$')
                    return (1);
                i += 1;
            }
        }
        i += 1;
    }
    return (0);
}

int     how_mutch(char *s)
{
    int i;
    int count;

    i = 0;
    count = 0;
    while (s[i] != '\0')
    {
        if (s[i] == '\"' || s[i] == '\\' || s[i] == '$')
            count++;
        i += 1;
    }
    return (count);
}

char    *add_backslash(char *s)
{
    int i;
    int j;
    char *str;

    i = 0;
    j = how_mutch(s);
    if (!(str = (char *) ft_calloc(sizeof (char), ft_strlen(s) + (j * 2) + 1)))
        return (NULL);
    j = 0;
    while (s[i] != '\0')
    {
        if (s[i + 1] == '\"' || s[i + 1] == '\\' || s[i + 1] == '$')
        {
            str[j] = s[i];
            j += 1;
            str[j] = '\\';
            j += 1;
            i += 1;
        }
        else
        {
            str[j] = s[i];
            i += 1;
            j += 1;
        }
    }
    str[j] = '\0';
    return (str);
}