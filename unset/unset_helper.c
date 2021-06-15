/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kait-mar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 17:37:44 by kait-mar          #+#    #+#             */
/*   Updated: 2021/04/18 17:23:35 by kait-mar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	delete_in_env_helper(char *s, char *split, int *check)
{
	int	i;

	i = in_match(s, split);
	if (i == 1)
	{
		i = ft_strcmp(split, "PWD");
		if (i == 0)
			g_global.pwd_on = 1;
		i = ft_strcmp(split, "OLDPWD");
		if (i == 0)
			g_global.oldpwd_on = 1;
		*check = 1;
		return (1);
	}
	return (0);
}

t_env	*increment_helper(int *count, t_env *tmp)
{
	tmp = tmp->next;
	*count += 1;
	return (tmp);
}

int	check_unset(char *str)
{
	if (ft_strncmp(str, "unset", 5) == 0)
		return (0);
	return (1);
}

char	*only_before_equal(char *str)
{
	int		i;
	char	*s;

	i = 0;
	s = (char *) ft_calloc(sizeof(char), ft_strlen(str));
	if (!s)
		return (NULL);
	while (str[i] != '=' && str[i] != '\0')
	{
		s[i] = str[i];
		i += 1;
	}
	s[i] = '\0';
	return (s);
}

t_env	*delete_in_env_core(t_env *env, char *split, int on)
{
	char	*s;
	int		j;
	int		count;
	int		check;
	t_env	*tmp;

	tmp = env;
	check = 0;
	count = 0;
	s = malloc(1);
	while (tmp != NULL)
	{
		free(s);
		s = only_before_equal(tmp->in_env);
		j = delete_in_env_helper(s, split, &check);
		if (j == 1)
			break ;
		tmp = increment_helper(&count, tmp);
	}
	free(s);
	if (check == 1)
		env = delete_list(env, count);
	else if (check == 0 && inside_quote(split) == 1 && on == 0)
		print_error(split);
	return (env);
}
