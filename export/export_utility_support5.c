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

void	export_init(void)
{
	int		i;
	char	*s;
	char	*string;
	char	**ss;
	char	*pwd_;
	int		pwd;
	int		shlvl;

	i = 0;
	pwd = 0;
	shlvl = 0;
	string = ft_strdup("SHLVL");
	pwd_ = ft_strdup("PWD");
	s = (char *) ft_calloc(sizeof(char ), 100);
	if (!(s))
		return ;
	ss = ft_calloc(sizeof (char *),
				   arguments_in(g_global.export->saver, i) + 3);
	while (g_global.export->saver[i])
	{
		ss[i] = ft_strdup(g_global.export->saver[i]);
		i += 1;
	}
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
	if (pwd == 0)
		pwd_init(s, &i);
	if (shlvl == 0)
		shlvl_init(s, &i);
	free(s);
	free(ss);
	ss = NULL;
	free(string);
	free(pwd_);
	string = NULL;
	s = NULL;
	pwd_ = NULL;
}
