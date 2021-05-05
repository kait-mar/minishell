/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molabhai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 14:18:46 by molabhai          #+#    #+#             */
/*   Updated: 2021/04/21 14:18:58 by molabhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_export_command(char **splits)
{
	int	i;

	i = 0;
	if (splits == NULL)
		return ;
	if (splits[i] != NULL)
	{
		while (splits[i])
		{
			free(splits[i]);
			splits[i] = NULL;
			i += 1;
		}
	}
	free(splits);
	splits = NULL;
}

char	*return_alloc_env(char *str)
{
	char	*env;
	int		len;

	len = ft_strlen(str);
	env = malloc(len + 1);
	len = 0;
	while (str[len] != '\0')
	{
		env[len] = str[len];
		len += 1;
	}
	env[len] = '\0';
	return (env);
}
