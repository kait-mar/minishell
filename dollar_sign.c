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

#include "minishell.h"





int     dollar_len(char *str, int i)
{
    int count;
    int j;

    count = 0;

    if (str[i] == '\\' && str[i + 1] == '$')
    {
        j = i;
        j += 2;
        count += 2;
    }
    else
        j = i + 1;
    while (str[j] != '\0' && str[j] != '$' && str[j] != '\\' && str[j] != ' '
           && str[j] != '>' &&  str[j] != '<' &&  str[j] != ';' && str[j] != '\t'
           && str[j] != '\'' && str[j] != '"' && str[j] != '|' && str[j] != ','\
           && str[j] != '[' && str[j] != ']')
    {
        count += 1;
        j += 1;
    }
    return (count);
}

char    *take_word(char *str, int i, int len)
{
    char *s;
    int j;

    j = 0;
    if (!(s = (char *) ft_calloc(sizeof (char), len + 1)))
        return (NULL);
    while (i <= len)
    {
        s[j] = str[i];
        i += 1;
        j += 1;
    }
    s[j] = '\0';
    return (s);
}

int    dollar_parsing(char *s)
{
    int i;

    i = 0;
    while (s[i] != '\0')
    {
        if (s[i] == '\'')
            return (0);
        else if (s[i] == '\"' && s[i + 1] != '$')
            return (0);
        i += 1;
    }
    return (1);
}


char    *take_after_equal(char *s)
{
    int i;
    int j;
    int on;
    int k;
    int one_time;
    char *string;

    i = 0;
    j = 0;
    on = 0;
    one_time = 0;
    while (s[i] != '\0')
    {
        if (s[i] == '=' && one_time == 0)
        {
            on = 1;
            k = i + 1;
            one_time = 1;
        }
        if (on == 1)
            j += 1;
        i += 1;
    }
    if (!(string = (char *) ft_calloc(sizeof (char), j + 1)))
        return (NULL);
    i = 0;
    while (s[k] != '\0')
    {
        string[i] = s[k];
        i += 1;
        k += 1;
    }
    string[i] = '\0';
    return (string);
}

char    *take_away_dollar(char *s)
{
    int i;
    int len;
    char *string;

    len = ft_strlen(s);
    if (!(string = (char *) ft_calloc(sizeof (char), len + 1)))
        return (NULL);
    i = 1;
    len = 0;
    while (s[i] != '\0')
    {
        string[len] = s[i];
        len += 1;
        i += 1;
    }
    string[len] = '\0';
    return (string);
}


int     check_backslash(char *s)
{
    int i;

    i = 0;
    while (s[i] != '\0')
    {
        if (s[i] == '$')
        {
            if (s[i - 1] == '\\')
                return (1);
        }
        i += 1;
    }
    return (0);
}

char    *chang_dollar(char *s, char **env, int *on)
{
    int i;
    char *string;
    char *ss;

    i = 0;
    ss = take_away_dollar(s);
    if (ft_strcmp(ss, "PWD") == 0 && g_pwd_on == 0)
    {
        string = ft_strdup(g_pwd_only);
        string = take_after_equal(string);
        *on = 1;
    }
    if (ft_strcmp(ss, "OLDPWD") == 0 && g_oldpwd_on == 0)
    {
        if (g_check == 0)
            string = ft_strdup("");
        else
        {
            string = ft_strdup(g_oldpwd_only);
            string = take_after_equal(string);
            *on = 1;
        }
    }
    else
    {
        while (env[i] != NULL && (check_backslash(s) == 0))
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
    if (check_backslash(s) == 1)
        string =ft_strdup(s);
    if (*on == 0)
    {
        string = ft_strdup("");
        *on = 2;
    }
    return (string);
}

int  counting_meta(char *s)
{
    int i;
    int count;

    i = 0;
    count = 0;
    while (s[i] != '\0')
    {
        if (s[i] == ';' || s[i] == '|'
            || s[i] == '<' || s[i] == '>')
        {
            if (s[i] == '>' &&  s[i + 1] == '>')
                i += 1;
            count += 1;
        }
        i += 1;
    }
    return (count);
}

char    *ignoring_meta(char *s)
{
    int i;
    int len;
    int j;
    char *string;

    i = 0;
    len = counting_meta(s);
    len += ft_strlen(s);
    j = 0;
    if (!(string = (char *) ft_calloc(sizeof (char ), len + 2)))
        return (NULL);
    while (s[i] != '\0')
    {
        string[j] = s[i];
        if (s[i + 1] == ';' || s[i + 1] == '|'
            || s[i + 1] == '<' || s[i + 1] == '>')
        {
            j += 1;
            string[j] = '\\';
        }
        i += 1;
        j += 1;
    }
    string[j] = '\0';
    return (string);
}

char    *realloc_input(char *str, char *s, int len, int string_len, int i)
{
    int o;
    int len_before;
    int len_after;
    int len_cmd;
    int j;
    char *string;

    len_after = 0;
    len_before = 0;
    len_cmd = ft_strlen(s);
    o = 0;
    j = 0;
    while (o < i && str[o] != '\0')
    {
        len_before += 1;
        o += 1;
    }
     o += (len + 1);
    while (str[o] != '\0')
    {
        len_after += 1;
        o += 1;
    }
    if (!(string = (char *) ft_calloc(sizeof (char), (len_cmd + len_after + len_before) + 1)))
        return (NULL);
    i = 0;
    while (len_before > 0)
    {
        string[i] = str[i];
        i += 1;
        len_before--;
    }
    s = ignoring_meta(s);
    while (len_cmd >= 0 && s[j] != '\0')
    {
        string[i] = s[j];
        i += 1;
        j += 1;
        len_cmd--;
    }
    string[i] = '\0';
    len_before  = string_len + 1;
    while (len_after > 0)
    {
        string[i] = str[len_before];
        len_after--;
        i += 1;
        len_before += 1;
    }
    string[i] = '\0';
    return (string);
}



char    *chang_dollar_sign(char *str, char **env)
{
    int i;
    int j;
    int on;
    char *s;
    char *changed;
    int valid;

    i = 0;
    on = 0;
    while (str[i] != '\0')
    {
        if (str[i] == '\'')
        {
            i += 1;
            while (str[i] !='\'' && str[i] !='\0')
                i += 1;
            if (str[i] == '\'')
                i += 1;
        }
        if ((str[i] == '$' && str[i + 1] != '?') || (str[i] == '\\' && str[i + 1] == '$'))
        {
            j = dollar_len(str, i);
            s = take_word(str, i, j + i);
            valid = dollar_parsing(s);
            if (valid == 1)
            {
                s = chang_dollar(s, env, &on);
               // if (on == 1)
               str = realloc_input(str, s, j, j + i, i);
            }
            //i = j;
        }
        if (str[i] == '\\' &&  str[i + 1] == '$')
            i += 2;
        else if (on != 2)
            i += 1;
        on = 0;
    }
    return (str);
}