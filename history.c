/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molabhai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 11:26:03 by molabhai          #+#    #+#             */
/*   Updated: 2021/04/06 11:26:06 by molabhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"


void    filling(t_assen *assen)
{
    int fd;
    int r;
    char *str;

    if ((fd = open(".minishell_history", O_RDWR)) != 1)
    {
        while ((r = get_next_line(fd, &str)) > 0)
        {
            append_assen(&assen, str);
        }
    }
}


char    *delete_char(char *string)
{
    string[ft_strlen(string ) - 1] = '\0';
    return (string);
}

int     find_re(char *string, int c)
{
    int i;

    i = 0;
    while (string[i] != '\0')
    {
        if (string[i] == c)
        {
            string[i] = '\0';
            return (TRUE);
        }
        i += 1;
    }
    return (FALSE);
}

char	*extend_re(char *str, char *s)
{
    char	*p_tr;
    int		i;
    int		j;

    p_tr = NULL;
    if (!(p_tr = (char *)ft_calloc((word_len(str, 0) +
                                    (s ? word_len(s, 0) : 0) + 1), sizeof(char))))
        return (NULL);
    i = 0;
    while (s && s[i] != '\0')
    {
        p_tr[i] = s[i];
        i++;
    }
    j = 0;
    while (str[j] != '\0')
    {
        p_tr[i] = str[j];
        i++;
        j++;
    }
    p_tr[i] = '\0';
    return (p_tr);
}

int     int_put(int c)
{
    write(1, &c, 1);
    return (0);
}

void    append_assen(t_assen **assen, char *cmd)
{
    t_assen *new_assen;
    t_assen *tmp;

    if (!(new_assen = (t_assen *) malloc(sizeof (t_assen))))
        return ;
    new_assen->cmd = ft_strdup(cmd);
    tmp = *assen;
    if (*assen == NULL)
    {
        *assen = new_assen;
        new_assen->prev = NULL;
        new_assen->next = NULL;
        return ;
    }
    while (tmp->next != NULL)
        tmp = tmp->next;
    tmp->next = new_assen;
    new_assen->next = NULL;
    new_assen->prev = tmp;
    return ;
}

t_history   init_hist(t_history history)
{
    char buffer[2048];
    char *buffer_address;

    history.tty_name = ttyname(STDIN_FILENO);
    history.term_type = getenv("TERM");
    if (tgetent(buffer, history.term_type) != 1)
        printf("No such term_type\n");
    buffer_address = (char *) malloc(ft_strlen(buffer));
    history.key_s = tgetstr("ks", &buffer_address);
    tputs(history.key_s, 2, int_put);
    history.up_arrow = tgetstr("ku", &buffer_address);
    history.down_arrow = tgetstr("kd", &buffer_address);
    history.key_e = tgetstr("ke", &buffer_address);
    history.clear = tgetstr("ce", &buffer_address);
    history.line_start = tgetstr("cr", &buffer_address);
    history.delete_char = tgetstr("dc", &buffer_address);
    history.delete_mode = tgetstr("dm", &buffer_address);
    history.exit_d_mode = tgetstr("ed", &buffer_address);
    return (history);
}