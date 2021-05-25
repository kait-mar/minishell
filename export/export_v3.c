/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_v3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kait-mar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 16:17:09 by kait-mar          #+#    #+#             */
/*   Updated: 2021/05/25 16:17:12 by kait-mar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*front_add_helper(char *s, char *to_append, int *i)
{
	while (to_append[*i] != '\0')
	{
		s[*i] = to_append[*i];
		*i += 1;
	}
	return (s);
}
