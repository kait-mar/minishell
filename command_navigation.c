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


void 	back_space(char **tmp, t_history history, char **temp, t_assen *climb)
{
	tputs(history.line_start, 0, int_put);
	tputs(history.clear, 0, int_put);
	prompt(g_global.in_signal);
	*tmp = delete_char(*tmp);
	if (climb->next == NULL)
		*temp = delete_char(*temp);
	ft_putstr(*tmp);
}

t_assen	*arrow_up(char **tmp, t_history history, t_assen *climb)
{
	tputs(history.line_start, 0, int_put);
	tputs(history.clear, 0, int_put);
	prompt(g_global.in_signal);
	if (climb->prev != NULL)
	{
		ft_putstr(climb->cmd);
		*tmp = ft_strdup(climb->cmd);
		if (climb->prev->prev != NULL)
			climb = climb->prev;
	}
	return (climb);
}

t_assen *arrow_down(t_history history, t_assen *climb, char **tmp, char **temp)
{
	tputs(history.line_start, 0, int_put);
	tputs(history.clear, 0, int_put);
	prompt(g_global.in_signal);
	if (climb->next != NULL)
	{
		climb = climb->next;
		ft_putstr(climb->cmd);
		*tmp = ft_strdup(climb->cmd);
	}
	else if (climb->next == NULL)
	{
		ft_putstr(*temp);
		*tmp = ft_strdup(*temp);
	}
	return (climb);
}

void 	string_extention(char **tmp, char **temp, char **str)
{
	*tmp = extend_re(*str, *tmp);
	*temp = extend_re(*str, *temp);
	*str = (char *) malloc(sizeof(char) * BUFFER + 1);
	if (*str == NULL)
		return ;
}

struct termios tty_init(int fd)
{
	struct termios save;
	struct termios tp;

	if (tcgetattr(fd, &tp) == -1)
		exit(-1);
	save = tp;
	tp.c_lflag &= ~(ICANON | ECHO);
	tp.c_cc[VMIN] = 0;
	tp.c_cc[VTIME] = 0;
	if (tcsetattr(fd, TCSANOW, &tp) == 1)
		exit (-1);
	return (save);
}

char 	*tty_loop(t_history history, t_assen *assen, t_assen *climb)
{
	char *str;
	int	r;
	char *temp;
	char    *tmp;

	str = (char *) malloc( BUFFER + 1);
	if (str == NULL)
		return (NULL);
	while (TRUE)
	{
		r = read(history.fd, str, BUFFER);
		str[r] = '\0';
		if (str[0] == 127)
			back_space(&tmp, history, &temp, climb);
		else
			ft_putstr(str);
		if (memcmp(str, history.up_arrow, 3) == 0)
			climb = arrow_up(&tmp, history, climb);
		if (memcmp(str, history.down_arrow, 3) == 0)
			climb = arrow_down(history, climb, &tmp, &temp);
		if (memcmp(str, history.down_arrow, 3) != 0
			&& memcmp(str, history.up_arrow, 3) != 0 && str[0] != 127)
			string_extention(&tmp, &temp, &str);
		if (find_re(tmp, '\n'))
		{
			if (ft_strcmp(tmp, "") != 0)
				append_assen(&assen, tmp);
			break ;
		}
	}
	return (tmp);
}

char   *reading_input(t_assen *assen)
{
	char	*str;
	char 	*tmp;
	t_history history;
	t_assen *climb;
	struct termios save;

	memset(&history, 0, sizeof (t_history));
    history = init_hist(history);
    history.fd = open(history.tty_name, O_RDWR | O_NOCTTY);
    climb = assen;
    while (climb->next !=  NULL)
        climb = climb->next;
    if (isatty(history.fd))
    {
    	save = tty_init(history.fd);
		tmp = tty_loop(history, assen, climb);
    }
    if (tcsetattr(history.fd, TCSANOW, &save) == 1)
        exit (-1);
    return (tmp);
}

