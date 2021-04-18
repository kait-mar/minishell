/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_helper2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kait-mar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 17:23:42 by kait-mar          #+#    #+#             */
/*   Updated: 2021/04/18 17:23:44 by kait-mar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**copy_all(t_env *take_env, char **env)
{
	int	i;

	i = 0;
	while (take_env != NULL)
	{
		env[i] = ft_strdup(take_env->in_env);
		i += 1;
		take_env = take_env->next;
	}
	if (env[i] == NULL)
		return (env);
	else
	{
		while (env[i] != NULL)
		{
			env[i] = NULL;
			i += 1;
		}
	}
	return (env);
}

void	unset_command(char **env, char *str, int *status)
{
	t_env		*take_env;
	char		**splits;
	int			i;

	i = 0;
	*status = 0;
	take_env = filling_env(env);
	splits = take_only_carac(str);
	take_env = delete_in_env(take_env, splits, i, status);
	env = copy_all(take_env, env);
    take_env = filling_env(g_global.export->saver);
    splits = take_only_carac(str);
    i = 1;
    take_env = delete_in_env(take_env, splits, i, status);
    g_global.export->saver = copy_all(take_env, g_global.export->saver);
}