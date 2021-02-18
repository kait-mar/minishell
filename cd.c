/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kait-mar <kait-mar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 17:46:24 by molabhai          #+#    #+#             */
/*   Updated: 2021/01/19 15:28:07 by kait-mar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <dirent.h>
#include "./Libft/libft.h"
#include <errno.h>

char     *reading_input(void)
{
	char	*str;
	int		i;

	str = NULL;
	i = get_next_line(1, &str);
	if (str == NULL || i == 0)
	{
		printf("ctr-D is detected\n");
		exit(EXIT_SUCCESS);
	}
	return (str);
}

char		**split_to_tokens(char *str)
{
	char	**splits;
	int		check;

	splits = ft_split(str, ' ');
	return (splits);
}

/*
char 	**taking_command(char *str)
{
	char **splits;

	str = reading_input(str);
	if ((splits = split_to_tokens(str)) == NULL)
		return (NULL);
	
	return (splits);
}*/

void 	cd_command(char *argument, int *status)
{
	char *str;
	char *s;

	if (argument == NULL)
		return ;
	if (!(str = ft_calloc(sizeof(char), 100)))
		return ;
	s = without_that(argument, '"' );
	if (ft_strncmp(s, "", 1) == 0)
	    s = ft_strdup("/Users/molabhai");
	if (chdir(s) < 0)
	{
	    ft_printf("%s\n", strerror(errno));
		*status = 1;
	}
	else
        *status = 0;
	free(s);
	s = NULL;
}