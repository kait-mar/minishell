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
			if (splits[i])
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

void	fill_shlvl(char **ss, char **env, int i, int *shlvl)
{
	char	*s;

	s = ft_itoa(check_shlvl(ss[i]));
	env[i] = append("SHLVL=", s);
	free(s);
	s = NULL;
	*shlvl = 1;
}

void	fill_pwd(char **ss, int i, int *pwd)
{
	if (g_global.pwd_only)
		free(g_global.pwd_only);
	g_global.pwd_only = ft_strdup(ss[i]);
	*pwd = 1;
}

int	alpha(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!(ft_isalnum(s[i]) || s[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}
