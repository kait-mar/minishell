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
	int		pwd;
	int		shlvl;

	i = 0;
	pwd = 0;
	shlvl = 0;
	s = (char *) ft_calloc(sizeof(char ), 100);
	if (!(s))
		return ;
	while (g_global.export->saver[i])
	{
		if (match("PWD", g_global.export->saver[i]) == 1)
			pwd = 1;
		else if (match("SHLVL", g_global.export->saver[i]) == 1)
			shlvl = 1;
		i += 1;
	}
	if (pwd == 0)
		pwd_init(s, &i);
	if (shlvl == 0)
		shlvl_init(s, &i);
}
