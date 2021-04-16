/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utility_two_support2.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molabhai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 14:11:05 by molabhai          #+#    #+#             */
/*   Updated: 2021/04/16 14:11:08 by molabhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pwd_init(char *s, int *i)
{
	char	*string;

	getcwd(s, 100);
	string = append("PWD=", s);
	g_global.export->saver[*i] = ft_strdup(string);
	*i += 1;
}

void	shlvl_init(char *s, int *i)
{
	char	*string;

	string = append("SHLVL=", "1");
	g_global.export->saver[*i] = ft_strdup(string);
	*i += 1;
}

void	pwd_env(char *s, char **env, int *i)
{
	char	*string;

	getcwd(s, 100);
	string = append("PWD=", s);
	env[*i] = ft_strdup(string);
	g_global.pwd_only = ft_strdup(env[*i]);
	*i += 1;
	env[*i] = NULL;
}

void	shlvl_env(char **env, int *i)
{
	char	*string;

	string = append("SHLVL=", "1");
	env[*i] = ft_strdup(string);
	*i += 1;
	env[*i] = NULL;
}

void	start_env(char **env, int *i)
{
	char	*ss;
	char	*string;

	ss = findin_env(env);
	string = append("_=", ss);
	string = ft_strjoin(string, "/env");
	env[*i] = ft_strdup(string);
	*i += 1;
	env[*i] = NULL;
}
