/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molabhai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 17:46:24 by molabhai          #+#    #+#             */
/*   Updated: 2020/12/05 14:54:55 by molabhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <dirent.h>
#include <errno.h>

char     *reading_input(char *str)
{
	get_next_line(0, &str);
	return (str);
}

char		**split_to_tokens(char *str)
{
	char	**splits;
	int		check;

	splits = ft_split(str, ' ');
	return (splits);
}
		
char 	**taking_command(char *str)
{
	char **splits;

	str = reading_input(str);
	if ((splits = split_to_tokens(str)) == NULL)
		return (NULL);
	
	return (splits);
}

void	cd_command(char *argument, int argument_on)
{
	char *str;
	char *s;

	if (argument == NULL)
		return ;
	if (!(str = ft_calloc(sizeof(char), 100)))
		return ;
	s = without_that(argument, '"' );
	if (chdir(s) < 0)
	{
		if (errno == 2)
			ft_printf("%s: No such file or directory\n", s);
		else
			ft_printf("errno == > %d\n", errno);
	}
}