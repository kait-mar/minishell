/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_support_two.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molabhai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 14:52:29 by molabhai          #+#    #+#             */
/*   Updated: 2021/04/14 14:52:31 by molabhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_export	*put_in_export(char *splits, int *on, t_export *export)
{
	int		k;

	k = 0;
	export_realloc();
	splits = error_reformulation(splits);
	while (g_global.export->saver[k])
	{
		if (match(g_global.export->saver[k], splits) == 1)
		{
			*on = 1;
			free_global_exp(splits, k);
		}
		k += 1;
	}
	if (*on == 0)
		g_global.export->saver[k] = ft_strdup(splits);
	g_global.export->saver[k + 1] = NULL;
	if (export->flag == 0)
		export->flag = 3;
	if (splits)
		free(splits);
	return (export);
}

t_export	*export_loop(char *splits, t_export *export, int on, int *j)
{
	splits = split_reformulation(splits);
	if (check_exp_lex(splits) == 1)
	{
		export->argument[*j] = ft_strdup(splits);
		export->argument[*j] = es_for_quote(export->argument[*j]);
		export->flag = 1;
		*j += 1;
	}
	if ((alpha(splits)
			&& last_check(splits, 1) == 0
			&& (no_space(splits) == 0)) || (check_exp_lex(splits) == 1))
		export = put_in_export(splits, &on, export);
	else
	{
		splits = error_reformulation(splits);
		ft_printf("minishell: export: `%s': not a valid identifier\n", splits);
		free(splits);
		*(g_global.status) = 1;
		export->flag = 0;
	}
	return (export);
}

t_export	*export_global(t_export *export)
{
	int	i;

	i = 0;
	while (g_global.export->saver[i])
	{
		if (in_it(g_global.export->saver[i]) == 1)
			g_global.export->saver[i] = add_backs(g_global.export->saver[i]);
		export->env[i] = front_append(g_global.export->saver[i], "declare -x ");
		i += 1;
	}
	export->flag = 2;
	return (export);
}

void	filling_export_env(char **env, char *export_argument)
{
	int		i;
	int		stop;
	char	*env_free;

	i = 0;
	stop = 0;
	while (env[i] != NULL)
	{
		if (match(env[i], export_argument) == 1)
		{
			env_free = env[i];
			env[i] = ft_strdup(export_argument);
			free(env_free);
			stop = 1;
		}
		i += 1;
	}
	if (env[i] == NULL && stop == 0)
	{
		env[i] = ft_strdup(export_argument);
		env[i + 1] = NULL;
	}
}

void	printing_filling_env(t_export *export, char **env)
{
	int	j;

	j = 0;
	if (export->flag == 1)
	{
		while (export->argument[j] != NULL)
		{
			filling_export_env(env, export->argument[j]);
			j += 1;
		}
	}
	else if (export->flag == 2)
	{
		while (export->env[j])
		{
			write(1, export->env[j], ft_strlen(export->env[j]));
			write(1, "\n", 1);
			j += 1;
		}
	}
}
