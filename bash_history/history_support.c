/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_support.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molabhai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 13:37:14 by molabhai          #+#    #+#             */
/*   Updated: 2021/04/10 13:37:15 by molabhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	append_assen(t_assen **assen, char *cmd)
{
	t_assen	*new_assen;
	t_assen	*tmp;

	new_assen = (t_assen *) malloc(sizeof (t_assen));
	if (new_assen == NULL)
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

t_history	init_hist(t_history history)
{
	history.tty_name = ttyname(STDIN_FILENO);
	history.term_type = getenv("TERM");
	if (tgetent(0, history.term_type) != 1)
		ft_printf("No such term_type\n");
	history.key_s = tgetstr("ks", 0);
	tputs(history.key_s, 2, int_put);
	history.up_arrow = tgetstr("ku", 0);
	history.down_arrow = tgetstr("kd", 0);
	history.key_e = tgetstr("ke", 0);
	history.clear = tgetstr("ce", 0);
	history.line_start = tgetstr("cr", 0);
	history.delete_char = tgetstr("dc", 0);
	history.delete_mode = tgetstr("dm", 0);
	history.exit_d_mode = tgetstr("ed", 0);
	history.fd = open(history.tty_name, O_RDWR | O_NOCTTY);
	return (history);
}

void	signals_in_read(char **tmp, char **temp, char *str)
{
	if (*tmp && ft_strcmp(*tmp, "") == 0)
		g_global.signal_input = 0;
	if (g_global.signal_input == 1 && str[0] != 4)
	{
		if (*tmp)
			free(*tmp);
		if (*temp)
			free(*temp);
		*tmp = NULL;
		*temp = NULL;
		g_global.signal_input = 0;
	}
}
