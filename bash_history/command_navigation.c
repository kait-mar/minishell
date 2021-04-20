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

#include "../minishell.h"

void 	back_space(char **tmp, t_history history, char **temp, t_assen *climb)
{
	if (*tmp == NULL)
		*tmp = ft_strdup("");
	if (*temp == NULL)
		*temp = ft_strdup("");
	tputs(history.line_start, 0, int_put);
	tputs(history.clear, 0, int_put);
	prompt();
	*tmp = delete_char(*tmp);
	if (climb->next == NULL)
		*temp = delete_char(*temp);
	ft_putstr(*tmp);
}

t_assen	*arrow_up(char **tmp, t_history history, t_assen *climb)
{
	tputs(history.line_start, 0, int_put);
	tputs(history.clear, 0, int_put);
	prompt();
	if (climb->prev != NULL)
	{
		ft_putstr(climb->cmd);
		*tmp = ft_strdup(climb->cmd);
		if (climb->prev->prev != NULL)
			climb = climb->prev;
	}
	return (climb);
}

t_assen	*arrow_down(t_history history, t_assen *climb, char **tmp, char **temp)
{
	tputs(history.line_start, 0, int_put);
	tputs(history.clear, 0, int_put);
	prompt();
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
	char	*temp_free;
	char 	*tmp_free;

	temp_free = *tmp;
	*tmp = extend_re(*str, *tmp);
	free(temp_free);
	tmp_free = *temp;
	*temp = extend_re(*str, *temp);
	free(tmp_free);
	/**str = (char *) malloc(sizeof(char) * BUFFER + 1);
	if (*str == NULL)
		return ;*/
}

char	*reading_input(t_assen *assen)
{
	char			*str;
	char			*tmp;
	t_history		history;
	t_assen			*climb;
	struct termios	save;

	memset(&history, 0, sizeof (t_history));
	history = init_hist(history);
	history.fd = open(history.tty_name, O_RDWR | O_NOCTTY);
	climb = assen;
	while (climb->next != NULL)
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
