/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molabhai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 17:46:24 by molabhai          #+#    #+#             */
/*   Updated: 2020/11/30 17:49:52 by molabhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "get_next_line.h"

char     *reading_input(char *str)
{
	get_next_line(1, &str);
	return (str);
}
char 	*taking_command(char *str)
{
	str = reading_input(str);
	return (str);
}


int		main()
{
	char *str = NULL;

	str = taking_command(str);
	printf("=== > %s \n", str);
	return(0);
}
