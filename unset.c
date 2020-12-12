/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molabhai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 12:08:00 by molabhai          #+#    #+#             */
/*   Updated: 2020/12/11 19:22:59 by molabhai         ###   ########.fr       */
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


int		in_match(char *s1, char *s2)
{
	if (ft_strncmp(s1, s2, ft_strlen(s1)) == 0)
		return (1);
	return (0);
}


t_env		*delete_list(t_env *env, int count)
{
	t_env	*tmp;

	tmp = env;
	while (count > 1)
	{
		tmp = tmp->next;
		count--;
	}
	tmp->next = tmp->next->next;
	return (env);
}

t_env		*delete_in_env(t_env *env, char **splits)
{
	char	*s;
	int		i;
	int 	count;
	int		check;
	t_env	*tmp;

	i = 1;
	count = 0;
	check = 0;
	tmp = env;
	while (splits[i] != NULL)
	{
		while (tmp != NULL)
		{
			s = only_before_equal(tmp->in_env);
			if (in_match(s, splits[i]) == 1)
			{
				check = 1;
				break ;
			}
			tmp = tmp->next;
			count += 1;
		}
		if (check == 1)
			env = delete_list(env, count); 
		count = 0;
		tmp = env;
		i += 1;
	}
	return (env);
}

t_env		*adding_last(t_env *head, int i, char *env)
{
	t_env	*s;
	t_env	*tmp;

	if (!(tmp = (t_env *) malloc(sizeof(t_env))))
		return (NULL);
	tmp->in_env = ft_strdup(env);
	tmp->next = NULL;
	if (i == 0)
		head = tmp;
	else
	{
		s = head;
		while (s->next != NULL)
			s = s->next;	
		s->next = tmp;
	}
	return (head);
}

t_env	*filling_env(char **env)
{
	t_env		*take_env;
	int			i;

	i = 0;
	while (env[i] != '\0')
	{
		take_env = adding_last(take_env, i, env[i]);
		i += 1;
	}
	return (take_env);
}

char	**copy_all(t_env *take_env, char **env)
{
	int	i;

	i = 0;
	while (take_env != NULL)
	{
		env[i] = ft_strdup(take_env->in_env);
		i += 1;
		take_env = take_env->next;
	}
	if (env[i] == NULL)
		return (env);
	else
	{
		while (env[i] != NULL)
		{
			env[i] = NULL;
			i += 1;
		}
	}
	return (env);
}

void	unset_command(char **env, char *str)
{
	t_env		*take_env;
	char		**splits;
	int			i;

	take_env = filling_env(env);
	splits = take_only_carac(str);
	take_env = delete_in_env(take_env, splits);
	env = copy_all(take_env, env);
	ft_printf("Here\n");

}
