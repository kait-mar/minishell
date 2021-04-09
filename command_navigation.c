/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_navigation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molabhai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 11:11:04 by molabhai          #+#    #+#             */
/*   Updated: 2021/04/09 11:11:06 by molabhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char   *reading_input(t_assen *assen)
{
    char	*str;
    int     r;
    char    *tmp;
    char    *temp;
    t_history history;
    t_assen *climb;
    int fd;
    char *clear;
    struct termios tp;
    struct termios save;

    str = NULL;
    tmp = NULL;
    temp = NULL;
    ft_memset(&history, 0, sizeof (t_history));
    if (!(str = (char *) malloc( BUFFER + 1)))
        return (NULL);
    history = init_hist(history);
    fd = open(history.tty_name, O_RDWR | O_NOCTTY);
    climb = assen;
    while (climb->next !=  NULL)
        climb = climb->next;
    if (isatty(fd))
    {
        if (tcgetattr(fd, &tp) == -1)
            exit(-1);
        save = tp;
        tp.c_lflag &= ~(ICANON | ECHO);
        tp.c_cc[VMIN] = 0;
        tp.c_cc[VTIME] = 0;
        if (tcsetattr(fd, TCSANOW, &tp) == 1)
            exit (-1);
        while (TRUE)
        {
            r = read(fd, str, BUFFER);
            str[r] = '\0';
            if (str[0] == 127)
            {
                tputs(history.line_start, 0, int_put);
                tputs(history.clear, 0, int_put);
                prompt(g_in_signal);
                tmp = delete_char(tmp);
                if (climb->next == NULL)
                    temp = delete_char(temp);
                ft_putstr(tmp);
            }
            else
                ft_putstr(str);
            if (memcmp(str, history.up_arrow, 3) == 0)
            {
                tputs(history.line_start, 0, int_put);
                tputs(history.clear, 0, int_put);
                prompt(g_in_signal);
                if (climb->prev != NULL)
                {
                    ft_putstr(climb->cmd);
                    tmp = ft_strdup(climb->cmd);
                    if (climb->prev->prev != NULL)
                        climb = climb->prev;
                }
            }
            if (memcmp(str, history.down_arrow, 3) == 0)
            {
                tputs(history.line_start, 0, int_put);
                tputs(history.clear, 0, int_put);
                prompt(g_in_signal);
                if (climb->next != NULL)
                {
                    climb = climb->next;
                    ft_putstr(climb->cmd);
                    tmp = ft_strdup(climb->cmd);
                }
                else if (climb->next == NULL)
                {
                    ft_putstr(temp);
                    tmp = ft_strdup(temp);
                }
            }
            if (memcmp(str, history.down_arrow, 3) != 0 && memcmp(str, history.up_arrow, 3) != 0 && str[0] != 127)
            {
                tmp = extend_re(str, tmp);
                temp = extend_re(str, temp);
                str = (char *) malloc(sizeof(char) * BUFFER + 1);
                if (str == NULL)
                    return (NULL);
            }
            if (find_re(tmp, '\n'))
            {
                if (ft_strcmp(tmp, "") != 0)
                    append_assen(&assen, tmp);
                break ;
            }
        }
    }
    if (tcsetattr(fd, TCSANOW, &save) == 1)
        exit (-1);
    free(str);
    return (tmp);
}

