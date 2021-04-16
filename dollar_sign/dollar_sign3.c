/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_sign3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kait-mar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 15:05:23 by kait-mar          #+#    #+#             */
/*   Updated: 2021/04/15 15:05:27 by kait-mar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
