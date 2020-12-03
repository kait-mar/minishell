/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utility.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molabhai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 19:01:30 by molabhai          #+#    #+#             */
/*   Updated: 2020/12/03 19:24:33 by molabhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*without_that(char *str, char c)
{
	int i;
	int j;
	char *s;

	if (!(s = ft_calloc(sizeof(char), ft_strlen(str))))
		return (NULL);
	i = 0;
		printf("Here\n");
	while (str[i])
	{
		if (str[i] == c)
			i += 1;
		else
		{
			s[i] = str[i];
			i += 1;
		}
	}
	return (s);
}
