/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semi_colon.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molabhai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 14:05:28 by molabhai          #+#    #+#             */
/*   Updated: 2021/02/18 14:05:30 by molabhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    *split_to_last_cmd(char *str)
{
    int i;
    int j;
    int k;
    char *s;

    i = 0;
    j = 0;
    while (str[i] != ';')
        i += 1;
    if (str[i] == ';')
        i += 1;
    k = i;
    while (str[i] != '\0')
    {
        j += 1;
        i +=1;
    }
    if (!(s = (char *) ft_calloc(sizeof (char), j + 1)))
        return (NULL);
    i = 0;
    while (str[k] != '\0')
    {
        s[i] = str[k];
        k += 1;
        i += 1;
    }
    s[i] = '\0';
    return (s);
}