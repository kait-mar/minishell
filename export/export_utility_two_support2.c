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
	char	*pwd;

	pwd = ft_strdup("PWD=");
	getcwd(s, 100);
	string = append(pwd, s);
	g_global.export->saver[*i] = ft_strdup(string);
	free(string);
	free(pwd);
	pwd = NULL;
	string = NULL;
	*i += 1;
}

void	shlvl_init(char *s, int *i)
{
	char	*string;
	char	*shlvl;
	char	*shlvl1;

	shlvl = ft_strdup("SHLVL=");
	shlvl1 = ft_strdup("1");
	string = append(shlvl, shlvl1);
	g_global.export->saver[*i] = ft_strdup(string);
	free(string);
	free(shlvl1);
	free(shlvl);
	string = NULL;
	shlvl1 = NULL;
	shlvl = NULL;
	*i += 1;
}

void	pwd_env(char *s, char **env, int *i)
{
	char	*string;

	getcwd(s, 100);
	string = append("PWD=", s);
	env[*i] = ft_strdup(string);
	free(string);
	string = NULL;
	if (g_global.pwd_only)
		free(g_global.pwd_only);
	g_global.pwd_only = ft_strdup(env[*i]);
	*i += 1;
	env[*i] = NULL;
}

void	shlvl_env(char **env, int *i)
{
	char	*string;

	string = append("SHLVL=", "1");
	env[*i] = ft_strdup(string);
	free(string);
	string = NULL;
	*i += 1;
	env[*i] = NULL;
}

void	start_env(char **env, int *i)
{
	char	*ss;
	char	*string;
	char	*free_string;

	ss = findin_env(env);
	string = append("_=", ss);
	free(ss);
	free_string = string;
	string = ft_strjoin(string, "/env");
	free(free_string);
	free_string = NULL;
	env[*i] = ft_strdup(string);
	free(string);
	string = NULL;
	*i += 1;
	env[*i] = NULL;
}
