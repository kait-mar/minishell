/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kait-mar <kait-mar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 16:19:20 by molabhai          #+#    #+#             */
/*   Updated: 2021/01/02 18:31:06 by kait-mar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	no_space(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == ' ')
			return (1);
		i += 1;
	}
	return (0);
}

int	check_shlvl(char *s)
{
	char				*number;
	long				nmb;

	number = only_after_equal(s);
	nmb = ft_atoi(number);
	free(number);
	number = NULL;
	if (nmb >= 709 && nmb < INT32_MAX)
	{
		ft_printf("%s (%ld) too high, resetting to 1\n", SHLVL_ERROR, nmb + 1);
		return (1);
	}
	else if (nmb >= INT32_MAX || nmb < 0)
		return (0);
	return (nmb + 1);
}

int	check_quote(char *str)
{
	int	i;
	int	on;

	i = 0;
	on = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' && str[i - 1] != '\\')
			on = 1;
		i += 1;
	}
	g_global.check_single_quote = on;
	return (on);
}

int	check_double_quote(char *str)
{
	int	i;
	int	on;

	i = 0;
	on = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\"' && str[i - 1] != '\\')
			on = 1;
		i += 1;
	}
	g_global.check_double_quote = on;
	return (on);
}

void	export_realloc(void)
{
	int			i;
	t_export	*tmp;

	tmp = filling_tmp();
	filling_global(tmp);
	i = 0;
	while (tmp->saver[i])
	{
		free(tmp->saver[i]);
		tmp->saver[i] = NULL;
		i += 1;
	}
	free(tmp->saver);
	tmp->saver = NULL;
	free(tmp);
	tmp = NULL;
}
