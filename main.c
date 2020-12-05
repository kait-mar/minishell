/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molabhai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 18:18:33 by molabhai          #+#    #+#             */
/*   Updated: 2020/12/05 12:12:08 by molabhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



int		check_wich_command(char *str)
{
	if (ft_strncmp(str, "cd", 2) == 0 && (ft_isalpha(str[2]) == 0))
		return (1);
	/* Here CHECK your command is lexically correct*/
	return (0);
}

int		main(int ac, char **av, char **env)
{
	char *str;
	t_command_cd *cd;
	char **splits;
	pid_t  pid1;
	int		status;
	char	*pwd;
	int i;

	str = NULL;
	pwd = NULL;
	cd = malloc(sizeof(t_command_cd));
	if (cd == NULL)
		return (-1);
	while (1)
	{
		str = reading_input(str);
		str = ft_strtrim(str, "\t");
		splits = split_to_tokens(str);
		i = how_mutch_argument(str, 0);
		if (i > 0)
		{
			i = how_mutch_argument(str, 2);
			splits[0] = ft_strtrim(splits[0], "\t");
			if (i == 1)
				splits[1] = ft_strtrim(splits[1], "\t");
			else if (i == 0)
				splits[1] = ft_strdup("/Users/molabhai");
			if (check_wich_command(splits[0]) == 1)
				pwd = cd_command(splits[1], i);
			/* Add ure main command Here
			 * Example:
			 * if (check_wich_command(*****))
			 * 		main_function
			 */ 
			else
				ft_printf("Command [%s] doesnt exist\n", splits[0]);
		}
	}
	return(0);
}
