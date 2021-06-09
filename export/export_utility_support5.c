/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utility_support5.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molabhai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 14:48:49 by molabhai          #+#    #+#             */
/*   Updated: 2021/04/16 14:48:51 by molabhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_free_ex(int pwd, int shlvl, char *string, int *i)
{
	if (pwd == 0)
		pwd_init(i);
	if (shlvl == 0)
		shlvl_init(i);
	free(string);
	string = NULL;
}

void	free_again(char **ss, char *pwd_)
{
	free(ss);
	ss = NULL;
	free(pwd_);
	pwd_ = NULL;
}

void	free_export_init(char **ss)
{
	char	*string;
	int		i;
	char	*pwd_;
	int		pwd;
	int		shlvl;

	pwd = 0;
	shlvl = 0;
	string = ft_strdup("SHLVL");
	pwd_ = ft_strdup("PWD");
	i = 0;
	while (ss[i])
	{
		if (match(pwd_, ss[i]) == 1)
			pwd = 1;
		else if (match(string, ss[i]) == 1)
			shlvl = 1;
		free(ss[i]);
		ss[i] = NULL;
		i += 1;
	}
	free_free_ex(pwd, shlvl, string, &i);
	free_again(ss, pwd_);
}

void	export_init(void)
{
	int		i;
	char	**ss;

	i = 0;
	ss = ft_calloc(sizeof(char *),
			arguments_in(g_global.export->saver, i) + 3);
	while (g_global.export->saver[i])
	{
		ss[i] = ft_strdup(g_global.export->saver[i]);
		i += 1;
	}
	free_export_init(ss);
}
