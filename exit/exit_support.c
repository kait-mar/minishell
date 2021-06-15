/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_support.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molabhai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 13:54:54 by molabhai          #+#    #+#             */
/*   Updated: 2021/04/18 13:54:55 by molabhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	filling_history(int fd, t_assen *move)
{
	if (dup2(fd, 1) == -1)
		ft_printf("%s\n", strerror(errno));
	while (move != NULL)
	{
		ft_printf("%s\n", move->cmd);
		move = move->next;
	}
	close(fd);
}

void	last_things(char *s, int *status)
{
	if (check_is_num(s) == 1)
	{
		ft_printf("%s%s: %s\n", EXIT_ERROR, s, "numeric argument required");
		*status = 255;
	}
	else
		*status = ft_atois(s);
	write(1, "exit\n", 5);
	exit(*status % 256);
}

long long	ft_atois(const char *str)
{
	long		i;
	int			res;
	int			neg;

	i = 0;
	res = 0;
	neg = 0;
	while (go_nexts(str[i]) != '\0')
		i++;
	if (str[i] == '-')
	{
		neg = 1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	res = results((char *)str, neg, i, res);
	return (res);
}

int	exit_command_void(int *status, char *s)
{
	char	**split;

	split = ft_split(s, ' ');
	if (split[1] != NULL)
	{
		ft_printf("minishell: exit: too many arguments\n");
		*status = 1;
		return (0);
	}
	return (1);
}
