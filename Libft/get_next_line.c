/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molabhai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 18:40:09 by molabhai          #+#    #+#             */
/*   Updated: 2020/11/30 19:05:13 by molabhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	word_len(char *str, int i)
{
	int	j;

	j = 0;
	while (str[j] != '\0')
	{
		if (str[j] == '\n' && i == 1)
			return (j);
		j++;
	}
	return (j);
}

int	search(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\n')
		{
			g_in_line = 1;
			str[i] = '\0';
			return (TRUE);
		}
		i++;
	}
	return (FALSE);
}

char	*extend(char *str, char *s)
{
	char	*p_tr;
	int		i;
	int		j;

	p_tr = NULL;
	if (s)
		i = word_len(s, 0);
	else
		i = 0;
	p_tr = (char *)ft_calloc((word_len(str, 0) + i + 1), 1);
	if (!p_tr)
		return (NULL);
	i = 0;
	while (s && s[i] != '\0')
	{
		p_tr[i] = s[i];
		i++;
	}
	j = 0;
	while (str[j] != '\0')
		p_tr[i++] = str[j++];
	p_tr[i] = '\0';
	free(str);
	free(s);
	return (p_tr);
}

void	ft_to_frees(char *str, char *o_tmp)
{
	free(str);
	free(o_tmp);
}

int	get_next_line(int fd, char **line)
{
	char		*str;
	static char	*ptr;
	char		*tmp;
	char		*o_tmp;
	int			k;

	o_tmp = NULL;
	if (return_rest(&ptr, &line[0], &o_tmp, &tmp) != NULL)
		return (1);
	str = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (fd < 0 || !line || read(fd, NULL, 0) < 0 || !str)
		return (-1);
	k = read(fd, str, BUFFER_SIZE);
	while (k > 0)
	{
		str[k] = '\0';
		o_tmp = extend(str, o_tmp);
		str = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
		if (return_line(&ptr, &o_tmp, &line[0], str) != NULL)
			return (1);
		k = read(fd, str, BUFFER_SIZE);
	}
	return_free_last(&tmp, &ptr, &o_tmp, &line[0]);
	ft_to_frees(str, o_tmp);
	return (0);
}
