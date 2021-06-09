/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   espace_character_helper.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kait-mar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 14:00:55 by kait-mar          #+#    #+#             */
/*   Updated: 2021/04/17 14:00:58 by kait-mar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	active(char *str, int i)
{
	int	count;

	count = 0;
	if (i > 0 && str[i - 1] == '\\')
	{
		i -= 1;
		while (str[i] == '\\')
		{
			i -= 1;
			count += 1;
		}
		if ((count % 2) == 0)
			return (1);
		else
			return (0);
	}
	return (1);
}

int	check_escape_meta(char *str, int i)
{
	while (str[i] == '\\')
		i += 1;
	if (str[i] == '>' || str[i] == '<' || str[i] == '|' || str[i] == ';')
		return (1);
	return (0);
}

int	check_escape_dollar(char *str, int i)
{
	while (str[i] == '\\')
		i += 1;
	if (str[i] == '$')
		return (1);
	return (0);
}

int	count_escape(char *str, int i)
{
	int	count;

	count = 0;
	while (str[i] == '\\')
	{
		i += 1;
		count += 1;
	}
	return (count);
}
