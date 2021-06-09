/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_support.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molabhai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 17:11:31 by molabhai          #+#    #+#             */
/*   Updated: 2021/04/19 17:11:35 by molabhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pwd_command(int *status, int exept)
{
	char	*str;

	str = (char *) ft_calloc(sizeof(char), 100);
	if (!(str))
		return ;
	if (exept == 1)
	{
		*status = 1;
		ft_printf("usage: pwd [-L | -P]\n");
		return ;
	}
	if (getcwd(str, 100) == NULL)
	{
		ft_printf("%s\n", strerror(errno));
		*status = 11;
	}
	ft_printf("%s\n", str);
	free(str);
	str = NULL;
	*status = 0;
}
