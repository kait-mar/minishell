/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utility_two.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molabhai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 18:01:31 by molabhai          #+#    #+#             */
/*   Updated: 2020/12/10 13:40:32 by molabhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


char	*front_append(char *string, char *to_append)
{
	char *s;
	int i;
	int j;

	if (!(s = (char *) malloc(sizeof(char) * (ft_strlen(string) + ft_strlen(to_append) + 1))))
		return (NULL);
	i = 0;
	while (to_append[i] != '\0')
	{
		s[i] = to_append[i];
		i += 1;
	}
	j = 0;
	while (string[j] != '\0')
	{
		s[i] = string[j];
		i += 1;
		j += 1;
	}
	s[i] = '\0';
	return (s);
}
