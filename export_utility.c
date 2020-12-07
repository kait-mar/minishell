/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utility.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molabhai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 11:56:12 by molabhai          #+#    #+#             */
/*   Updated: 2020/12/07 13:25:32 by molabhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int		check_exp_lex(char *str)
{
	int i;

	i = 0;
	if (ft_isalpha(str[i]) == 0)
		return (0);
	while (ft_isalpha(str[i]))
		i += 1;
	if (str[i] == '=')
		return (1);
	return (0);
}
