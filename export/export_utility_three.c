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
	int		i;
	int		on;

	i = 0;
	on = 0;
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

t_export	*check_export(char **splits, char **env, t_export *export)
{
	int	i;
	int	j;
	int	on;

	on = 0;
	j = 0;
	i = 0;
	export = check_export_init(splits, export);
	export->flag = 0;
	if (splits[i] == NULL)
		splits[i] = ft_strdup("");
	if (how_mutch_arguments(splits, i) == 1)
	{
		while (splits[i] != NULL)
		{
			export = export_loop(splits[i], export, on, j);
			i += 1;
		}
	}
	else
		export = export_global(export);
	return (export);
}

void	export_command(char **env, char *str, int *status, t_export *export)
{
	int		j;
	char	**splits;

	j = 0;
	splits = take_only_carac_for_export(str);
	export = check_export(splits, env, export);
	printing_filling_env(export, status, env);
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
		ft_printf("%s\n", env[i]);
		i += 1;
	}
	*status = 0;
}