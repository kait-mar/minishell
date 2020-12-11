/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molabhai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 12:08:00 by molabhai          #+#    #+#             */
/*   Updated: 2020/12/11 14:53:40 by molabhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int		check_unset(char *str)
{
	int i;

	i = 0;
	if (ft_strncmp(str, "unset", 5) == 0)
		return (0);
	return (1);
}

char	*only_before_equal(char *str)
{
	int i;
	char *s;

	i = 0;
	if (!(s = (char *) ft_calloc(sizeof(char), ft_strlen(str))))
		return (NULL);
	while (str[i] != '=')
	{
		s[i] = str[i];
		i += 1;
	}
	s[i] = '\0';
	return (s);
}

int		to_delete(char *argument, char **env)
{
	int i;
	char *s;

	i = 0;
	while (env[i] != '\0')
	{
		s = ft_strdup(env[i]);
		s = only_before_equal(s);
		if ((ft_strncmp(s, argument, ft_strlen(s))) == 0)
			return (i);
		i += 1;
	}
	return (0);
}
	
void	unset_command(char **env, char *str)
{
	t_unset		*unset;
	int			i;

	if (!(unset = (t_unset *) malloc(sizeof(t_unset))))	
		return ;
	unset->argument = take_only_carac(str);

	i = to_delete(unset->argument[1], env);
	free(env[i]);
	env[i] = NULL;
}
