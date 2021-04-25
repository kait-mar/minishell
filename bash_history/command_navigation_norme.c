/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_navigation_norme.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molabhai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 16:40:25 by molabhai          #+#    #+#             */
/*   Updated: 2021/04/12 16:40:26 by molabhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

struct termios	tty_init(int fd)
{
	struct termios	save;
	struct termios	tp;

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

char	*ctrl_d(void)
{
	ft_putchar('\n');
	return (ft_strdup("exit \n"));
}

t_assen 	*read_l(char **temp, char **tmp, t_history history, t_assen *climb, char *str)
{
	int		r;

	r = read(history.fd, str, BUFFER);
	str[r] = '\0';
	if (r > 0)
	{
		if (str[0] == 127)
			back_space(tmp, history, temp, climb);
		else if (str[0] == 4 && ft_strcmp(*tmp, "") == 0)
			*tmp = ctrl_d();
		else if (str[0] != 4 && str[0] != 127)
			ft_putstr(str);
		if (history.up_arrow != NULL && ft_memcmp(str, history.up_arrow, 3) == 0)
			climb = arrow_up(tmp, history, climb);
		if (history.down_arrow != NULL
			&& ft_memcmp(str, history.down_arrow, 3) == 0)
			climb = arrow_down(history, climb, tmp, temp);
		if ((history.down_arrow != NULL
			 && ft_memcmp(str, history.down_arrow, 3) != 0)
			&& (history.up_arrow != NULL
				&& ft_memcmp(str, history.up_arrow, 3) != 0) && str[0] != 127)
			string_extention(tmp, temp, str);
	}
//	free(str);
//	str = NULL;
	return (climb);
}

char	*tty_loop(t_history history, t_assen *assen, t_assen *climb, char *str)
{
	char	*temp;
	char	*tmp;

	temp = NULL;
	tmp = NULL;
	//memset(&history, 0, sizeof (t_history));
	// history = init_hist(history);
	while (TRUE)
	{
		climb = read_l(&temp, &tmp, history, climb, str);
		if (tmp && find_re(tmp, '\n'))
		{
			if (ft_strcmp(tmp, "") != 0)
				append_assen(&assen, tmp);
			break ;
		}
	}
	return (tmp);
}
