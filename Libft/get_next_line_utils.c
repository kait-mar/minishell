/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molabhai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 14:26:27 by molabhai          #+#    #+#             */
/*   Updated: 2020/12/03 16:39:45 by molabhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*return_line(char **ptr, char **o_tmp, char **line, char *str)
{
	char	*tmp;

	if (search(*o_tmp) == TRUE)
	{
		tmp = *ptr;
		*ptr = ft_strdup(*o_tmp + word_len(*o_tmp, 1) + 1);
		if (tmp)
		{
			free(tmp);
			tmp = NULL;
		}
		*line = ft_strdup(*o_tmp);
		free(*o_tmp);
		free(str);
		return (*line);
	}
	return (NULL);
}

char	*return_rest(char **ptr, char **line, char **o_tmp, char **tmp)
{
	if (*ptr)
	{
		if (search(*ptr) == TRUE)
		{
			*line = ft_strdup(*ptr);
			*tmp = *ptr;
			*ptr = ft_strdup(*ptr + word_len(*ptr, 1) + 1);
			if (*tmp)
			{
				free(*tmp);
				tmp = NULL;
			}
			return (*line);
		}
		else
			*o_tmp = ft_strdup(*ptr);
	}
	return (NULL);
}

void	return_free_last(char **tmp, char **ptr, char **o_tmp, char **line)
{
	*tmp = *ptr;
	if (tmp)
	{
		free(*tmp);
		*tmp = NULL;
		*ptr = NULL;
	}
	if (*o_tmp)
		*line = ft_strdup(*o_tmp);
	else
		*line = ft_strdup("");
}
