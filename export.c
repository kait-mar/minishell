/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molabhai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 16:19:20 by molabhai          #+#    #+#             */
/*   Updated: 2020/12/05 17:28:19 by molabhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"


int		check_quote(char *str)
{
	int i;
	int on;

	 i = 0;
	 on = 0;
	 while (str[i] != '\0')
	 {
		 if (str[i] == '\'')
			 on = 1;
		 i += 1;
	 }
	 return (on);
}

int		check_double_quote(char *str)
{
	int i;
	int on;

	 i = 0;
	 on = 0;
	 while (str[i] != '\0')
	 {
		 if (str[i] == '\"')
			 on = 1;
		 i += 1;
	 }
	 return (on);
}

int		check_env(char *str)
{
	char *s;
	int i;
	int on;

	i = 0;
	on = 0;
	s = "env";
	if (check_quote(str) == 1)
		str = without_that(str, '\'');
	else if (check_double_quote(str) == 1)
		str = without_that(str, '\"');
	if (check_quote(str) == 0 && check_double_quote(str) == 0)
	{
		str = ft_toStrLower(str);
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
	else
		on = 1;
	return (on);
}

void	env_command(char **str)
{
	int i;

	i = 0;
	while (str[i])
	{
		ft_printf("%s\n", str[i]);
		i += 1;
	}
}

