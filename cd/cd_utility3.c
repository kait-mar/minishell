/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utility3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kait-mar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 15:19:11 by kait-mar          #+#    #+#             */
/*   Updated: 2021/04/15 15:19:13 by kait-mar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void 	cd_command(char *argument, int *status, char **env)
{
	char		*s;
	char		*ss;
	static int	first_time = 0;

	s = NULL;
	if (argument == NULL)
		return ;
	ss = take_only(argument);
	if (check_only_single_double(ss) == 0)
	{
		s = cd_free(s, ss, env);
	}
	old_pwd(env);
	if (check_only_single_double(ss) == 0)
	{
		if (cd_command_helper(status, env, &s, first_time) == 0)
		{
			if (ss)
				free(ss);
			return ;
		}
	}
	cd_command_helper2(env, &first_time);
	if (ss)
		free(ss);
}

char	*cd_free(char *s, char *ss, char **env)
{
	char		*free_s;
	char		*x;
	int			i;

	i = 0;
	s = without_that(ss, '\"');
	free_s = s;
	s = without_that(ss, '\'');
	free(free_s);
	if (ft_strncmp(s, "", 1) == 0)
	{
		if (s)
			free(s);
		while (env[i])
		{
			x = take_before_equal(env[i]);
			if (ft_strcmp(x, "HOME") == 0)
				s = take_after_equal(env[i]);
			i += 1;
		}
	}
	return (s);
}

char	*take_only(char *s)
{
	int		i;
	char	*string;

	i = 0;
	if (s[i] == '\'')
	{
		i += 1;
		if (s[i] == '\'')
			string = take_only_helper(s, i);
		else
			string = take_only_helper2(s, i, '\'');
	}
	else if (s[i] == '\"')
	{
		i += 1;
		string = take_only_core(s, i);
		if (string == NULL)
			return (NULL);
	}
	else
		string = take_only_helper3(s);
	return (string);
}

int	cd_command_helper(int *status, char **env, char **s, int first_time)
{
	if (chdir(*s) < 0)
	{
		ft_printf("minishell: cd: %s: %s\n", *s, strerror(errno));
		if (first_time == 0)
			remove_old_pwd(env);
		free(*s);
		*s = NULL;
		*status = 1;
		return (0);
	}
	else
		*status = 0;
	free(*s);
	*s = NULL;
	return (1);
}

void	cd_command_helper2(char **env, int *first_time)
{
	char	*str;

	str = ft_calloc(sizeof(char), 100);
	if (str == NULL)
		return ;
	if (getcwd(str, 100) == NULL)
		ft_printf("%s\n", strerror(errno));
	new_pwd(env, str);
	g_global.pwd_on = 0;
	g_global.check = 1;
	*first_time = 1;
	free(str);
	str = NULL;
}
