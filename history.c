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

void	filling(t_assen *assen)
{
	int		fd;
	char	*str;

	fd = open(".minishell_history", O_RDWR);
	if (fd != 1)
	{
		while (get_next_line(fd, &str) > 0)
			append_assen(&assen, str);
	}
}

char	*delete_char(char *string)
{
	string[ft_strlen(string) - 1] = '\0';
	return (string);
}

int	find_re(char *string, int c)
{
	int	i;

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
	int		len;

	if (s)
		len = word_len(s, 0);
	else
		len = 0;
	p_tr = (char *) ft_calloc((word_len(str, 0) + len + 1), sizeof(char));
	if (p_tr == NULL)
		return (NULL);
	i = 0;
	while (s && s[i] != '\0')
	{
		p_tr[i] = s[i];
		i += 1;
	}
	j = 0;
	while (str[j] != '\0')
		p_tr[i++] = str[j++];
	p_tr[i] = '\0';
	return (p_tr);
}

int	int_put(int c)
{
	write(1, &c, 1);
	return (0);
}
