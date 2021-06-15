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

int	in_match(char *s1, char *s2)
{
	if (ft_strncmp(s1, s2, ft_strlen(s2)) == 0)
		return (1);
	return (0);
}

char	**copy_all(t_env *take_env, char **env)
{
	int		i;
	t_env	*tmp;

	i = 0;
	tmp = take_env;
	while (tmp != NULL)
	{
		if (env[i])
			free(env[i]);
		env[i] = ft_strdup(tmp->in_env);
		i += 1;
		tmp = tmp->next;
	}
	while (env[i] != NULL)
	{
		if (env[i] && match_shlvl(env[i], "SHLVL=") == 0)
			free(env[i]);
		env[i] = NULL;
		i += 1;
	}
	env[i] = NULL;
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
	take_env = delete_in_env(take_env, splits, i);
	env = copy_all(take_env, env);
	free_struct(take_env);
	take_env = filling_env(g_global.export->saver);
	to_free(splits);
	splits = take_only_carac(str);
	i = 1;
	take_env = delete_in_env(take_env, splits, i);
	g_global.export->saver = copy_all(take_env, g_global.export->saver);
	to_free(splits);
	free_struct(take_env);
}

void	free_struct(t_env *lst)
{
	t_env	*tmp;

	while (lst != NULL)
	{
		tmp = lst;
		if (lst->in_env)
			free(lst->in_env);
		lst = lst->next;
		free(tmp);
		tmp = NULL;
	}
}

void	print_error(char *split)
{
	ft_printf("minishell: unset: `%s': not a valid identifier\n",
		   without_that(split, '\''));
	*(g_global.status) = 1;
}
