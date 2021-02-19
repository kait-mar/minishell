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


char    *chang_dollar_sign(char *str, char **env)
{
    int i;
    char *s;
    int on;
    int j;

    i = 0;
    while (str[i] != '\0')
    {
        if (str[i] == '$')
        {
            on = 1;
            break ;
        }
        i += 1;
    }
    if (str[i] == '$')
        i += 1;
    j = i;
    while (str[j] != '$' && str[j] != ' ' && str[j] != '\\' && str[j] != '|' && str[j] != '>'
        && str[j] != '<')
    {
        j += 1;
    }
    if (!(s = (char *) ft_calloc(sizeof (char ), j + 1)))
        return (NULL);
    j = 0;
    while (str[i] != '$' && str[i] != ' ' && str[i] != '\\' && str[i] != '|' && str[i] != '>'
           && str[i] != '<')
    {
        s[j] = str[i];
        i += 1;
        j += 1;
    }
    s[j] = '\0';
    return s;
}
