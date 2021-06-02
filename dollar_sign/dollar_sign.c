/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_sign.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molabhai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 16:27:14 by molabhai          #+#    #+#             */
/*   Updated: 2021/02/18 16:27:16 by molabhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*chang_dollar(char *s, char **env, int *on)
{
	int		escape;
	char	*string;
	char	*ss;

	escape = count_escap(s);
	ss = take_away_dollar(s);
	string = NULL;
	if (ft_strcmp(ss, "PWD") == 0 && g_global.pwd_on == 0)
		string = string_pwd(on);
	else if (ft_strcmp(ss, "OLDPWD") == 0 && g_global.oldpwd_on == 0)
		string = string_oldpwd(on);
	else
		string = string_change_dollar(ss, on, env);
	if (*on == 0)
	{
		if (string)
			free(string);
		string = ft_strdup("");
		*on = 2;
	}
	string = string_frees(string, escape, ss, *on);
	free(ss);
	free(s);
	return (string);
}

char	*chang_dollar_sign(char *str, char **env)
{
	t_sign	lst;

	memset(&lst, 0, sizeof (t_sign));
	while (str[lst.i] != '\0')
	{
		if (str[lst.i] == '\'')
		{
			if (check_front_quote(str, lst.i) == 1)
			{
				lst.i += 1;
				continue ;
			}
			lst.i += 1;
			while (str[lst.i] != '\'' && str[lst.i] != '\0')
				lst.i += 1;
			if (str[lst.i] == '\'')
				lst.i += 1;
		}
		lst = change_dollar_core(lst, &str, env);
	}
	return (str);
}

char	*str_free(char *str, char *s)
{
	free(s);
	return (str);
}

int	check_front_quote(char *s, int i)
{
	int	count;

	count = 0;
	while (i >= 0)
	{
		if (s[i] == '"')
			count += 1;
		i -= 1;
	}
	if ((count % 2) == 0)
		return (0);
	return (1);
}
