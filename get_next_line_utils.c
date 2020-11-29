/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kait-mar <kait-mar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 21:54:36 by kait-mar          #+#    #+#             */
/*   Updated: 2019/11/15 04:18:46 by kait-mar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strdup(const char *s1)
{
	char	*str;
	int		i;

	i = 0;
	while (s1[i] != '\0')
		i++;
	str = malloc(sizeof(char) * (i + 1));
	if (str == 0)
		return (0);
	i = -1;
	while (s1[++i] != '\0')
		str[i] = s1[i];
	str[i] = '\0';
	return (str);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*string;
	int		k;

	if (s1 == 0 || s2 == 0)
		return (0);
	i = 0;
	j = 0;
	while (s1[i] != '\0')
		i++;
	while (s2[j] != '\0')
		j++;
	string = malloc(i + j + 1);
	if (string == 0)
		return (0);
	i = 0;
	j = 0;
	k = 0;
	while (s1[i] != '\0')
		string[k++] = s1[i++];
	while (s2[j] != '\0')
		string[k++] = s2[j++];
	string[k] = '\0';
	return (string);
}

int		ft_strlen(const char *str)
{
	char	*string;
	int		i;

	string = (char*)str;
	i = 0;
	while (*string++ != '\0')
		i++;
	return (i);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	int		n;
	int		r;
	int		k;

	ptr = malloc(count * size);
	if (ptr)
	{
		n = count * size / sizeof(long);
		r = count * size % sizeof(long);
		k = 0;
		while (n--)
			((long *)ptr)[k++] = 0;
		while (r--)
			((char *)ptr)[k * sizeof(long) + r] = 0;
		return (ptr);
	}
	return (NULL);
}

char	*ft_substr(char const *s, int start, int len)
{
	int		i;
	char	*substring;

	if (s == 0)
		return (0);
	if (start > ft_strlen(s))
		len = 0;
	substring = malloc(len + 1);
	if (substring == 0)
		return (NULL);
	i = 0;
	while (i < len && s[start] != '\0' && start < ft_strlen(s))
	{
		substring[i] = s[start];
		i++;
		start++;
	}
	substring[i] = '\0';
	return (substring);
}
