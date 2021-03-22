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
	if (!(s = (char *) ft_calloc(sizeof(char), ft_strlen(str) + 1)))
		return (NULL);
	while (str[i] != '=' &&  str[i] != '\0')
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
	if (tmp->next->next != NULL) {
        tmp->next = tmp->next->next;
    }
	else
	    tmp->next = NULL;
	return (env);
}

int     inside_quote(char *s)
{
    int i;

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

t_env		*delete_in_env(t_env *env, char **splits, int on, int *status)
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
			    if (ft_strcmp(splits[i], "PWD") == 0)
			        g_pwd_on = 1;
			    else if (ft_strcmp(splits[i], "OLDPWD") == 0)
			        g_oldpwd_on = 1;
				check = 1;
				break ;
			}
			tmp = tmp->next;
			count += 1;
		}
		if (check == 1)
            env = delete_list(env, count);
		else if (check == 0 && inside_quote(splits[i]) == 1 && on == 0)
        {
            ft_printf("minishell: unset: `%s': not a valid identifier\n", without_that(splits[i], '\''));
            *status = 1;
        }
		check = 0;
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
	while (env[i])
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

void	unset_command(char **env, char *str, int *status)
{
	t_env		*take_env;
	char		**splits;
	int			i;

	i = 0;
	*status = 0;
	take_env = filling_env(env);
	splits = take_only_carac(str);
	take_env = delete_in_env(take_env, splits, i, status);
	env = copy_all(take_env, env);
    take_env = filling_env(g_export->saver);
    splits = take_only_carac(str);
    i = 1;
    take_env = delete_in_env(take_env, splits, i, status);
    g_export->saver = copy_all(take_env, g_export->saver);
}