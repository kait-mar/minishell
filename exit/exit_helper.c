/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kait-mar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 15:04:36 by kait-mar          #+#    #+#             */
/*   Updated: 2021/04/19 15:04:39 by kait-mar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
    exit_command_support(s, status);
}

void    exit_command_support(char *s, int *status)
{
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
