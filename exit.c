/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molabhai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 08:56:58 by molabhai          #+#    #+#             */
/*   Updated: 2020/12/31 08:57:00 by molabhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     check_exit(char *str)
{
    char *s;

    s = take_first_word(str);
    if ((ft_strncmp(str, "exit", 4) == 0) && (ft_isalpha(str[4]) == 0))
        return (1);
    return (0);
}

void        exit_command(int status, char *s)
{
    if (s[0] == '\0')
        exit(status);
    else
    {
        status = ft_atoi(s);
        exit(status);
    }
}
