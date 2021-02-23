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
#include <errno.h>

char     *reading_input(void)
{
	char	*str;
	int		i;
	int     on;
	int     k;
	int check;
	char    *s;

	str = NULL;
	i = 0;
	k = 0;
	check = 0;
	int j=0;
	while (i == 0)
	{
	    if (k == 0 ||  (g_in_line == 0 && i == 0))
        {
            i = get_next_line(1, &str);
            if (k == 0)
                s = ft_strdup(str);
            if (g_in_line == 1 && i == 1)
            {
                g_in_line = 0;
                return (s);
            }
        }
        if (ft_strcmp(str, "") == 0 && i == 0 && check == 0)
        {
            ft_printf("exit\n");
            exit(EXIT_SUCCESS);
        }
        else if (i == 0 && ft_strcmp(str, "") != 0 && k == 0)
            check = 1;
        k += 1;
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