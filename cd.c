/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molabhai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 17:46:24 by molabhai          #+#    #+#             */
/*   Updated: 2020/12/05 12:12:53 by molabhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <dirent.h>
#include "./Libft/libft.h"
#include <errno.h>

char     *reading_input(char *str)
{
	get_next_line(1, &str);
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

char	*cd_command(char *argument, int argument_on)
{
	char *str;
	char *s;

	if (argument == NULL)
		return (NULL);
	if (!(str = ft_calloc(sizeof(char), 100)))
		return (NULL);
	s = without_that(argument, '"' );
	if (chdir(s) < 0)
	{
		if (errno == 2)
			ft_printf("No such file or directory\n");
		else
			ft_printf("errno == > %d\n", errno);
	}
	getcwd(str, 100);
	ft_printf("PWD ==> %s\n", str);
	return (str);
}
