/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molabhai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 17:46:24 by molabhai          #+#    #+#             */
/*   Updated: 2020/12/03 19:24:55 by molabhai         ###   ########.fr       */
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

static char 		**checking(char **splits, int *check)
{
	int i;

	i = 0;
	*check = 0;
	while (splits[i])
	{
		if (strncmp(splits[i], "cd", 2) == 0)
		{
			*check += 1;
		}
		else if (i == 1)
				*check += 1;
		i += 1;
	}
	return (splits);
}

char		**split_to_tokens(char *str)
{
	char	**splits;
	int		check;

//	cd = malloc(sizeof(char) * (sizeof(t_command_cd)));
	splits = ft_split(str, ' ');
	splits = checking(splits, &check);
	if (check != 2)
		return (NULL);
//	printf("==> %s\n", cd->token);
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

char	*cd_command(char *argument)
{
	char *str;

	if (!(str = ft_calloc(sizeof(char), 100)))
		return (NULL);
	char *s;

	s = without_that("\"labhairil\"", '"' );
	printf("str ==> %s\n", s);
	printf("argument ==> %s\n", argument);
	if (chdir(argument) < 0)
	{
		if (errno == 2)
			ft_putstr("No such file or directory\n");
		else
			ft_putstr("Error in cd command\n");
		printf("errno == > %d\n", errno);
	}
	getcwd(str, 100);
	return (str);
}
