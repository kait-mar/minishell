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

#include "minishell.h"

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
	char	buffer[2048];
	char	*buffer_address;

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
