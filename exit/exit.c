/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molabhai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 08:56:58 by molabhai          #+#    #+#             */
/*   Updated: 2020/12/31 08:57:00 by molabhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_exit(char *str)
{
	if ((ft_strncmp(str, "exit", 4) == 0) && (ft_isalnum(str[4]) == 0))
		return (1);
	return (0);
}

int	check_is_num(char *s)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '-' || s[i] == '+')
			j += 1;
		if (ft_isdigit(s[i]) == 0
			&& (s[i] != ' ' || s[i] != '\t') && (j > 1 || j == 0))
			return (1);
		i += 1;
	}
	return (0);
}

long long	results(char *str, int neg, int i, int res)
{
	int	carac;

	while (str[i] >= '0' && str[i] <= '9')
	{
		carac = str[i] - '0';
		res = carac % 10 + res * 10;
		if (!(str[i + 1] >= '0' && str[i + 1] <= '9'))
		{
			if (neg != 0)
				res = -res;
			return (res);
		}
		i++;
	}
	if (neg != 0)
		res = -res;
	return (res);
}

int	go_nexts(char str)
{
	if ((str >= 9 && str <= 13) || str == ' ')
		return (1);
	return (0);
}

void	exit_command(int *status, char *s)
{
	if (exit_command_void(status, s) == 0)
		return ;
	s = take_only(s);
	s = without_that(s, '\"');
	s = without_that(s, '\'');
	if (s[0] == '\0')
	{
		write(1, "exit\n", 5);
		exit(*status);
	}
	else
		last_things(s, status);
}
