/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meta_support2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kait-mar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 18:51:48 by kait-mar          #+#    #+#             */
/*   Updated: 2021/05/27 18:51:53 by kait-mar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_meta	*split_it_header(char **splits, t_meta *global, int *i)
{
	if (check_meta(splits[*i]) == TRUE)
		global = meta_in(splits, global, i);
	else if (check_meta(splits[*i]) == FALSE)
		global = meta_out(splits, global, i);
	global->next = NULL;
	return (global);
}
