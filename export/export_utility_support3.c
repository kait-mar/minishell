/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utility_support3.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molabhai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 14:28:48 by molabhai          #+#    #+#             */
/*   Updated: 2021/04/16 14:28:51 by molabhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	filling_export(char **env)
{
	int		i;

	i = 0;
	g_global.export = malloc(sizeof(t_export));
	if (!(g_global.export))
		return ;
	g_global.export->saver = ft_calloc(sizeof(char *),
			arguments_in(env, i) + 3);
	if (!(g_global.export->saver))
		return ;
	while (env[i])
	{
		g_global.export->saver[i] = ft_strdup(env[i]);
		i += 1;
	}
	export_init();
	env_init(env);
}

int	in_it(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '=')
		{
			if (s[i] == '\'')
				i += 1;
			while (s[i] != '\0' && s[i] != '\'')
			{
				if (s[i] == '\"' || s[i] == '\\' || s[i] == '$')
					return (1);
				i += 1;
			}
		}
		i += 1;
	}
	return (0);
}

int	how_mutch(char *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\"' || s[i] == '\\' || s[i] == '$')
			count++;
		i += 1;
	}
	return (count);
}

char	*add_backs(char *s)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = how_mutch(s);
	str = ft_calloc(sizeof(char), ft_strlen(s) + (j * 2) + 1);
	if (!(str))
		return (NULL);
	j = 0;
	while (s[i] != '\0')
	{
		if (s[i + 1] == '\"' || s[i + 1] == '\\' || s[i + 1] == '$')
		{
			str[j] = s[i];
			j += 1;
			str[j] = '\\';
			j += 1;
			i += 1;
		}
		else
			str[j++] = s[i++];
	}
	str[j] = '\0';
	return (str);
}

int	fill_env_init(char **env, int *pwd, int *shlvl, int *start)
{
	int		i;
	char	**ss;

	i = 0;
	ss = ft_calloc(sizeof(char *), arguments_in(env, i) + 3);
	while (env[i])
	{
		ss[i] = ft_strdup(env[i]);
		i += 1;
	}
	i = 0;
	while (ss[i])
	{
		if (match("PWD", ss[i]) == 1)
			fill_pwd(ss, i, pwd);
		else if (match("SHLVL", ss[i]) == 1)
			fill_shlvl(ss, env, i, shlvl);
		else if ((match("_", ss[i]) == 1))
			*start = 1;
		free(ss[i]);
		i += 1;
	}
	free(ss);
	ss = NULL;
	return (i);
}
