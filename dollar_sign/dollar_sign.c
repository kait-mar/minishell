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

int     count_escap(char *s)
{
    int i;
    int count;

    i = 0;
    count = 0;
    while (s[i] == '\\')
    {
        count += 1;
        i += 1;
    }
    return (count);
}

char    *adding_escape(char *s, int count)
{
    int i;
    int j;
    int len;
    char *str;

    i = 0;
    j = 0;
    len = ft_strlen(s) + count + 1;
    if (!(str = (char *) ft_calloc(sizeof (char ), len)))
        return (NULL);
    while (count > 0)
    {
        str[i] = '\\';
        i += 1;
        count -= 1;
    }
    while (s[j] != '\0')
    {
        str[i] = s[j];
        i += 1;
        j += 1;
    }
    str[i] = '\0';
    return (str);
}
int     dollar_len(char *str, int i)
{
    int count;
    int j;
    int k;

    j = 0;
    count = 0;
    while (str[i] == '\\')
    {
        i += 1;
        count += 1;
    }
    if (str[i] == '$')
    {
        i += 1;
        count += 1;
    }
    while (str[i] != '\0' && str[i] != '$' && str[i] != ' '
           && str[i] != '>' &&  str[i] != '<' &&  str[i] != ';' && str[i] != '\t'
           && str[i] != '\'' && str[i] != '"' && str[i] != '|' && str[i] != ','
           && str[i] != '[' && str[i] != ']')
    {
        count += 1;
        i += 1;
    }
    return (count);
}

char    *take_word(char *str, int i, int len)
{
    char *s;
    int j;
    int count;

    j = 0;
    count = 0;
    if (!(s = (char *) ft_calloc(sizeof (char), len + 1)))
        return (NULL);
    while (i < len)
    {
        s[j] = str[i];
        i += 1;
        j += 1;
    }
    s[j] = '\0';
    if (count > 0)
        s = adding_escape(s, count);
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
        else if (s[i] == '$' && active(s, i) == 0)
            return (0);
        else if (s[i] == '$' && (s[i + 1] == ' ' || s[i + 1] == '\0' || s[i + 1] == '\\'))
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
    free(s);
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
    if (s[0] == '\\')
    {
        i = 0;
        while (s[i] == '\\')
            i += 1;
        if (s[i] == '$')
            i += 1;
    }
    else
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
    o += (len );
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
    while (len_cmd >= 0 && s[j] != '\0')
    {
        string[i] = s[j];
        i += 1;
        j += 1;
        len_cmd--;
    }
    len_before  = string_len;
    while (len_after > 0)
    {
        string[i] = str[len_before];
        len_after--;
        i += 1;
        len_before += 1;
    }
    string[i] = '\0';
    free(str);
    return (string);
}



char    *chang_dollar_sign(char *str, char **env)
{
    int i;
    int j;
    int on;
    int len;
    char *s;
    int valid;
    int remove;
    int space_front;
    int space_back;

    i = 0;
    on = 0;
    remove = 0;
    space_front = 0;
    space_back = 0;
    s = NULL;
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
        if (str[i] == '$' && str[i + 1] == '?')
        {
                i += 2;        
        }
        else if ((str[i] == '$' && str[i + 1] != '?') || check_escape_dollar(str, i) == 1)
        {
            j = dollar_len(str, i);
            s = take_word(str, i, j + i);
            len = ft_strlen(s);
            valid = dollar_parsing(s);
            s = remove_escape_dollar(s);
            j = ft_strlen(s);
            if (valid == 1)
            {
                if (inside_quotes(str, i) == 1)
                    remove = 1;
                s = chang_dollar(s, env, &on);
				if (s[0] == ' ')
                    space_front = 1;
                if (s[ft_strlen(s) - 1] == ' ')
                    space_back = 1;
				if (str[i - 1] == '[' && str[i + j] == ']' && remove == 1)
                    s = rm_space_variable(s, 0);
                else if (str[i - 1] == '[' && str[i + j] != ']' && remove == 1)
                    s = rm_space_variable(s, 1);
                else if (str[i - 1] != '[' && str[i + j] == ']' && remove == 1)
                    s = rm_space_variable(s, 2);
                else if (remove == 1)
                    s = remove_space(s);
				if (escape_front_true(str, i) == 1 && space_front == 1 && inside_quotes(str, i) == 1)
                    s = add_front_space(s);
                if (escape_back_true(str, i) == 1 && space_back == 1)
                    s = add_back_space(s);
                else if ((str[i + j] == '$' && space_back == 1))
                    s = add_back_space(s);
            }
			str = realloc_input(str, s, j, len + i, i);
            len = ft_strlen(s);
            if (s)
            	free(s);
            i = len + i;
            remove = 0;
        }
       if (str[i] != '$' && str[i] != '\'' && str[i] != '\0' && check_escape_dollar(str, i) == 0)
           i += 1;
       on = 0;
    }
	return (str);
}