/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utility_three.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molabhai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 15:55:42 by molabhai          #+#    #+#             */
/*   Updated: 2021/04/14 15:55:45 by molabhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_env(char *str)
{
	int		on;

	if (check_quote(str) == 1)
		str = without_that(str, '\'');
	else if (check_double_quote(str) == 1)
		str = without_that(str, '\"');
	if (check_quote(str) == 0 && check_double_quote(str) == 0)
		on = return_env_on(str);
	else
		on = 1;
	return (on);
}

t_export	*check_export(char **splits, t_export *export)
{
	int	i;
	int	j;
	int	on;

	on = 0;
	j = 0;
	i = 0;
	export = check_export_init(splits, export);
	if (splits[i] == NULL)
		splits[i] = ft_strdup("");
	if (how_mutch_arguments(splits, i) == 1)
	{
		while (splits[i] != NULL)
		{
			export = export_loop(splits[i], export, on, &j);
			i += 1;
		}
	}
	else
		export = export_global(export);
	return (export);
}

void	export_command(char **env, char *str, t_export *export)
{
	char	**splits;

	splits = take_only_carac_for_export(str);
	export = check_export(splits, export);
	printing_filling_env(export, env);
	free_export_command(splits);
	if (export->env)
		free_export_command(export->env);
	if (export->argument)
		free_export_command(export->argument);
	free(export);
	export = NULL;
}

void	env_command(char **env, t_meta *meta, int *status)
{
	int	i;

	i = 0;
	if (ft_strncmp(meta->argument, "", ft_strlen(meta->argument)) != 0)
	{
		while (meta != NULL)
		{
			meta->argument = ft_strtrim(meta->argument, "\t");
			if (check_env(meta->argument) == 1)
			{
				ft_printf("Command [%s] doesnt exist\n", meta->argument);
				*status = 127;
				return ;
			}
			meta = meta->next;
		}
	}
	while (env[i])
	{
		write(1, env[i], ft_strlen(env[i]));
		write(1, "\n", 1);
		i += 1;
	}
	*status = 0;
}

void	free_global_exp(char *splits, int k)
{
	char	*global_free;

	global_free = g_global.export->saver[k];
	g_global.export->saver[k] = ft_strdup(splits);
	free(global_free);
}
