/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kait-mar <kait-mar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 22:05:53 by kait-mar          #+#    #+#             */
/*   Updated: 2019/11/18 04:34:43 by kait-mar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		find(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

int		ft_line(int i, char *string)
{
	if (i == -1)
		return (-1);
	if (i == 0 && find(string) == 0)
	{
		return (0);
	}
	else
		return (1);
}

int		position(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	return (i);
}

int		auxilliaire(char **s, int fd)
{
	char	*buff;
	int		i;
	char	*temp;

	if (!(buff = malloc(BUFFER_SIZE + 1)) || fd < 0)
		return (-1);
	while ((i = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		if (i < 0 || BUFFER_SIZE < 0 || fd < 0)
			return (-1);
		buff[i] = '\0';
		temp = ft_strjoin(*s, buff);
		if (temp == 0)
			return (-1);
		free(*s);
		*s = temp;
		if (find(buff))
			break ;
		free(buff);
		if (!(buff = malloc(BUFFER_SIZE + 1)))
			return (-1);
	}
	free(buff);
	return (i);
}

int		get_next_line(int fd, char **line)
{
	static char		*s;
	int				k;
	char			*temp;

	if (s == 0)
		s = ft_calloc(1, 1);
	k = auxilliaire(&s, fd);
	if (k == -1)
		return (-1);
	k = ft_line(k, s);
	*line = ft_substr(s, 0, position(s));
	if (find(s) == 1)
	{
		temp = ft_strdup(s + position(s) + 1);
		if (temp == 0)
			return (-1);
	}
	else
		temp = NULL;
	free(s);
	s = temp;
	return (k);
}
