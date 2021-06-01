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
		free(cmd);
		cmd = NULL;
		return ;
	}
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new_assen;
	new_assen->next = NULL;
	new_assen->prev = tmp;
	free(cmd);
	cmd = NULL;
	return ;
}

t_history	init_hist(t_history history)
{
	char	buffer[2048];

	history.tty_name = ttyname(STDIN_FILENO);
	history.term_type = getenv("TERM");
	if (tgetent(buffer, history.term_type) != 1)
		printf("No such term_type\n");
	history.tty_name = ttyname(STDIN_FILENO);
	g_global.buffer_address = malloc(ft_strlen(buffer));
	history.key_s = tgetstr("ks", &(g_global.buffer_address));
	tputs(history.key_s, 2, int_put);
	history.up_arrow = tgetstr("ku", &(g_global.buffer_address));
	history.down_arrow = tgetstr("kd", &(g_global.buffer_address));
	history.key_e = tgetstr("ke", &(g_global.buffer_address));
	history.clear = tgetstr("ce", &(g_global.buffer_address));
	history.line_start = tgetstr("cr", &(g_global.buffer_address));
	history.delete_char = tgetstr("dc", &(g_global.buffer_address));
	history.delete_mode = tgetstr("dm", &(g_global.buffer_address));
	history.exit_d_mode = tgetstr("ed", &(g_global.buffer_address));
	return (history);
}

void	signals_in_read(char **tmp, char **temp, char *str)
{
	if (ft_strcmp(*tmp, "") == 0)
		g_global.signal_input = 0;
	if (g_global.signal_input == 1 && str[0] != 4)
	{
		free(*tmp);
		free(*temp);
		*tmp = NULL;
		*temp = NULL;
		g_global.signal_input = 0;
	}
}
