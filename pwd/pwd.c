/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molabhai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 13:19:17 by molabhai          #+#    #+#             */
/*   Updated: 2020/12/22 18:17:22 by molabhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_isupper(int c)
{
	if (c >= 65 && c <= 90)
		return (1);
	return (0);
}

int	check_first_pwd(char *str)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (ft_isupper(str[i]) == 1)
			return (1);
		i += 1;
	}
	return (0);
}

int	check_after_first(char *str)
{
	int	i;

	i = 3;
	while (str[i] != '\0')
	{
		if (ft_isprint(str[i]) == 1)
			return (1);
		i += 1;
	}
	return (0);
}

int	check_pwd(char *str)
{
	int		i;
	char	*s;
	int		on;

	i = 0;
	on = 0;
	s = "pwd";
	while (str[i] != '\0' && i < 3)
	{
		if (str[i] != s[i])
			on = 1;
		i += 1;
	}
	if (ft_isalpha(str[i]))
		on = 1;
	return (on);
}
