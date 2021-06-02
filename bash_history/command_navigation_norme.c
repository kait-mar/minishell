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
	tp.c_lflag &= ~ (ICANON | ECHO);
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

t_assen	*read_l(char **temp, char **tmp, t_glb glb, char *str)
{
	int		r;

	r = read(glb.history.fd, str, BUFFER);
	str[r] = '\0';
	signals_in_read(tmp, temp, str);
	if (r > 0)
	{
		if (str[0] == 127)
			back_space(tmp, glb.history, temp, glb.climb);
		else if (str[0] == 4 && ((ft_strcmp(*tmp, "") == 0)
				|| g_global.signal_input == 1))
			*tmp = read_l_support(temp, tmp);
		else if (str[0] != 4 && str[0] != 127)
			ft_putstr(str);
		if (glb.history.up_arrow != NULL
			&& ft_memcmp(str, glb.history.up_arrow, 3) == 0)
			glb.climb = arrow_up(tmp, glb.history, glb.climb);
		if (glb.history.down_arrow != NULL
			&& ft_memcmp(str, glb.history.down_arrow, 3) == 0)
			glb.climb = arrow_down(glb.history, glb.climb, tmp, temp);
		if (condition_command(glb, str) && str[0] != 4)
			string_extention(tmp, temp, str);
	}
	return (glb.climb);
}

char	*tty_loop(t_assen *assen, t_glb glb, char *str)
{
	char	*temp;
	char	*tmp;

	temp = NULL;
	tmp = NULL;
	while (TRUE)
	{
		glb.climb = read_l(&temp, &tmp, glb, str);
		if (tmp && find_re(tmp, '\n'))
		{
			if (ft_strcmp(tmp, "") != 0)
				append_assen(&assen, tmp);
			break ;
		}
	}
	return (tmp);
}

char	*string_extention_helper(char *temp)
{
	free(temp);
	temp = NULL;
	return (temp);
}
