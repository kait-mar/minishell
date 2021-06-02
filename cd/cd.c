/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kait-mar <kait-mar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 17:46:24 by molabhai          #+#    #+#             */
/*   Updated: 2021/01/19 15:28:07 by kait-mar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*add_in(char *first, char *second)
{
	int		i;
	int		j;
	char	*s;
	int		len;

	len = ft_strlen(first);
	len += ft_strlen(second);
	i = 0;
	j = 0;
	s = (char *) ft_calloc(sizeof (char), len + 1);
	if (!s)
		return (NULL);
	while (first[i] != '\0')
	{
		s[i] = first[i];
		i += 1;
	}
	while (second[j] != '\0')
		s[i++] = second[j++];
	return (s);
}

int	find_old_pwd(char *s)
{
	if (ft_strncmp(s, "OLDPWD", 6) == 0)
		return (1);
	return (0);
}

int	find_pwd(char *s)
{
	if (ft_strncmp(s, "PWD", 3) == 0)
		return (1);
	return (0);
}

void	remove_old_pwd(char **env)
{
	int		i;
	char	*string;

	i = 0;
	string = ft_strdup("OLDPWD");
	while (env[i])
	{
		if (match(env[i], string) == 1)
		{
			free(env[i]);
			env[i] = NULL;
			break ;
		}
		i += 1;
	}
	free(string);
}
