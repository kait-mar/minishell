/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_support.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molabhai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 14:17:45 by molabhai          #+#    #+#             */
/*   Updated: 2021/04/14 14:17:50 by molabhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	filling_global(t_export *tmp)
{
	int	i;

	i = 0;
	g_global.export = malloc(sizeof(t_export));
	if (!(g_global.export))
		return ;
	g_global.export->saver = ft_calloc(sizeof(char *),
			arguments_in(tmp->saver, i) + 2);
	if (!(g_global.export->saver))
		return ;
	while (tmp->saver[i])
	{
		g_global.export->saver[i] = ft_strdup(tmp->saver[i]);
		i += 1;
	}
}

t_export	*filling_tmp(void)
{
	t_export	*tmp;
	int			i;

	tmp = malloc(sizeof(t_export));
	if (!(tmp))
		return (NULL);
	i = 0;
	tmp->saver = ft_calloc(sizeof(char *),
			arguments_in(g_global.export->saver, i) + 1);
	if (!(tmp->saver))
		return (NULL);
	while (g_global.export->saver[i])
	{
		tmp->saver[i] = ft_strdup(g_global.export->saver[i]);
		free(g_global.export->saver[i]);
		i += 1;
	}
	free(g_global.export->saver);
	free(g_global.export);
	return (tmp);
}

int	return_env_on(char *str)
{
	int		i;
	char	*s;
	int		on;

	s = "env";
	i = 0;
	on = 0;
	while (i < 3)
	{
		if (str[i] != s[i])
			on = 1;
		i += 1;
	}
	if (ft_isalpha(str[i]))
		on = 1;
	return (on);
}

t_export	*check_export_init(char **splits, t_export *export)
{
	int	i;

	i = 0;
	if (export == NULL)
	{
		export = malloc(sizeof(t_export));
		if (!(export))
			return (NULL);
		export->argument = ft_calloc(sizeof(char *),
				arguments_in(splits, i) + 1);
		if (!(export->argument))
			return (NULL);
		export->env = ft_calloc(sizeof(char *),
				arguments_in(g_global.export->saver, i) + 1);
		if (!(export->env))
			return (NULL);
	}
	return (export);
}

char	*split_reformulation(char *splits)
{
	char	*free_s;

	splits = ft_strtrim(splits, "\t");
	if (check_double_quote(splits) == 1
		&& check_double_inside_single(splits) == 0)
	{
		free_s = splits;
		splits = without_that(splits, '\"');
		free(free_s);
	}
	else if (check_quote(splits) == 1
		&& check_single_inside_double(splits) == 0)
	{
		free_s = splits;
		splits = without_that(splits, '\'');
		free(free_s);
	}
	return (splits);
}
