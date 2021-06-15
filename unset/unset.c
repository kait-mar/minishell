/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molabhai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 12:08:00 by molabhai          #+#    #+#             */
/*   Updated: 2020/12/23 16:42:38 by molabhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*delete_list(t_env *env, int count)
{
	t_env	*tmp;
	t_env	*s;

	tmp = env;
	while (count > 1)
	{
		tmp = tmp->next;
		count--;
	}
	if (tmp->next->next != NULL)
	{
		s = tmp->next;
		tmp->next = tmp->next->next;
		free(s->in_env);
		free(s);
	}
	else
	{
		free(tmp->next->in_env);
		free(tmp->next);
		tmp->next = NULL;
	}
	return (env);
}

int	inside_quote(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\'')
		{
			i += 1;
			if (s[i] == '\'')
				return (1);
			while (s[i] != '\'')
			{
				if (!ft_isalpha(s[i]) && s[i] != '\'')
					return (1);
				i += 1;
			}
		}
		i += 1;
	}
	return (0);
}

t_env	*delete_in_env(t_env *env, char **splits, int on)
{
	int	i;

	i = 0;
	while (splits[i] != NULL)
	{
		if (on == 0 && check_unset_tok(splits[i]) == 0)
			env = delete_in_env_core(env, splits[i], on);
		i += 1;
	}
	return (env);
}

t_env	*adding_last(t_env *head, int i, char *env)
{
	t_env	*s;
	t_env	*tmp;

	tmp = (t_env *)malloc(sizeof(t_env));
	if (!tmp)
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
	while (env[i])
	{
		take_env = adding_last(take_env, i, env[i]);
		i += 1;
	}
	return (take_env);
}
