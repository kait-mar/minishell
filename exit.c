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

int     check_is_num(char *s)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (s[i] != '\0')
    {
        if (s[i] == '-' || s[i] == '+')
            j += 1;
        if (ft_isdigit(s[i]) == 0 && (s[i] != ' ' ||  s[i] != '\t') && (j > 1 || j == 0))
            return (1);
        i += 1;
    }
    return (0);
}

long long 		results(char *str, int neg, int i, int res)
{
    int carac;

    while (str[i] >= '0' && str[i] <= '9')
    {
        carac = str[i] - '0';
        res = carac % 10 + res * 10;
        if (!(str[i + 1] >= '0' && str[i + 1] <= '9'))
        {
            if (neg != 0)
                res = -res;
            return (res);
        }
        i++;
    }
    if (neg != 0)
        res = -res;
    return (res);
}

int		go_nexts(char str)
{
    if ((str >= 9 && str <= 13) || str == ' ')
        return (1);
    return (0);
}

long long 		ft_atois(const char *str)
{
    long		i;
    int			res;
    int			neg;

    i = 0;
    res = 0;
    neg = 0;
    while (go_nexts(str[i]) != '\0')
        i++;
    if (str[i] == '-')
    {
        neg = 1;
        i++;
    }
    else if (str[i] == '+')
        i++;
    res = results((char *)str, neg, i, res);
    return (res);
}

void        exit_command(int *status, char *s, t_assen *assen)
{
    t_assen *move;
    int fd;
    pid_t pid;
    int stat;
    char **split;

    move = assen;
    if (move->next != NULL)
        move = move->next;
    split = ft_split(s, ' ');
    if (split[1] != NULL)
    {
        printf("minishell: exit: too many arguments\n");
        *status = 1;
        return ;
    }
    s = take_only(s);
    s = without_that(s, '\"');
    s = without_that(s, '\'');
    fd = open(".minishell_history", O_CREAT | O_APPEND | O_RDWR, S_IRWXU);
    if ((pid = fork()) > 0)
    {
            if (dup2(fd, 1) == -1)
                printf("%s\n", strerror(errno));
            while (move != NULL)
            {
                printf("%s\n", move->cmd);
                move = move->next;
            }
            close(fd);
    }
    waitpid(pid, &stat, WUNTRACED);
    if (s[0] == '\0')
	{
		exit(*status);
	}
	else
    {
        if (check_is_num(s) == 1)
        {
            ft_printf("minishell: exit: %s: %s\n", s, "numeric argument required");
            *status = 255;
        }
        else
            *status = ft_atois(s);
        exit(*status % 256);
    }
}