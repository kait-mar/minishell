/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_sign_utility.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molabhai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 13:27:39 by molabhai          #+#    #+#             */
/*   Updated: 2021/03/29 13:27:42 by molabhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     count_space_variable(char *s)
{
    int i;
    int count;

    i = 0;
    count = 0;
    if (s[i] == ' ')
    {
        count += 1;
        while (s[i] == ' ')
            i += 1;
    }
    while (ft_isprint(s[i]) && s[i] != '\0')
    {
        i += 1;
        count += 1;
        if (s[i] == ' ' && active(s, i) == 1)
        {
            count += 1;
            while (s[i] == ' ')
                i += 1;
        }
    }
    return (count);
}

int     only_space(char *s, int i)
{
    while (s[i] == ' ')
        i += 1;
    if (s[i] != '\0')
        return (0);
    return (1);
}

char    *rm_space_variable(char *s, int wich)
{
    int i;
    int j;
    char *str;

    i = 0;
    j = 0;
    if (!(str = (char *) malloc(sizeof (char) * count_space_variable(s) + 1)))
        return (NULL);
    if (s[i] == ' ')
    {
        if (wich == 1 || wich == 0)
            str[j++] = s[i++];
        while (s[i] == ' ')
            i += 1;
    }
    while (ft_isprint(s[i]) && s[i] != '\0')
    {
        str[j++] = s[i++];
        if (s[i] == ' ' && only_space(s, i) == 0)
        {
            str[j++] = s[i++];
            while (s[i] == ' ')
                i += 1;
        }
        else if (s[i] == ' ' && only_space(s, i) == 1)
        {
            if (wich == 2 || wich == 0)
               str[j++] = s[i++];
            while (s[i] == ' ')
                i += 1;
            break ;
        }
    }
    str[j] = '\0';
    return (str);
}

int     inside_quotes(char *s, int i)
{
    int count;

    count = 0;
    while (i > 0)
    {
        if (s[i] == '"')
            count += 1;
        i -= 1;
    }
    if ((count % 2) == 0)
        return (1);
    return (0);
}

int    escape_front_true(char *s, int i)
{
    int count;

    count = 0;
    i = i - 1;
    while (s[i] == ' ')
    {
        i -= 1;
        count += 1;
    }
    if (count > 1)
        return (1);
    return (0);
}

int     escape_back_true(char *s, int i)
{
    int count;

    count = 0;
    while (ft_isprint(s[i]))
        i += 1;
    if (s[i] == ' ')
        return (1);
    return (0);
}

char    *add_back_space(char *s)
{
    int i;
    int j;
    char *str;

    i = 0;
    j = 0;
    if (!(str = (char *) malloc(sizeof (char) * ft_strlen(s) + 2 )))
        return (NULL);
    while (s[i] != '\0')
        str[j++] = s[i++];
    str[j++] = ' ';
    str[j] = '\0';
    return (str);
}

char    *add_front_space(char *s)
{
    char *string;
    int len;
    int i;
    int j;

    i = 0;
    j = 0;
    len = ft_strlen(s) + 1;
    if (!(string = (char *) malloc(sizeof (char) * len + 1)))
        return (NULL);
    if (s[i] == '\\')
    {
        while (s[i] == '\\')
            s[j++] = s[i++];
    }
    string[j++] = ' ';
    while (s[i] != '\0')
        string[j++] = s[i++];
    string[j] = '\0';
    return (string);
}

int check_inside_front_quote(char *s, int i)
{
    i -= 1;
    if (ft_isprint(s[i]))
    {
        while (ft_isprint(s[i]) && s[i] != '$' && s[i] != '"')
            i -= 1;
        if (s[i] == '$')
            return (1);
        else
            return (0);
    }
    return (1);
}

int check_inside_back_quote(char *s, int i)
{
    i += 1;
    if (ft_isprint(s[i]))
    {
        while (ft_isprint(s[i]) && s[i] != '$' && s[i] != '"')
            i += 1;
        if (s[i] == '$')
            return (1);
        else
            return (0);
    }
    return (1);
}
