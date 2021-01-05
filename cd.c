/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molabhai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 17:46:24 by molabhai          #+#    #+#             */
/*   Updated: 2020/12/24 15:07:06 by molabhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <dirent.h>
#include "./Libft/libft.h"
#include <errno.h>

char     *reading_input(void)
{
	char	*str;

	str = NULL;
	get_next_line(1, &str);
	if (str == NULL)
		printf("str ==> %s\n", str);
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

char 	*cd_command(char *argument, int *status, int piping)
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
	    if (piping == 0)
    		ft_printf("%s\n", strerror(errno));
	    else if (piping == 1)
	        return (s);
		*status = 1;
	}
	else
        *status = 0;
	free(s);
	s = NULL;
    return (s);
}
