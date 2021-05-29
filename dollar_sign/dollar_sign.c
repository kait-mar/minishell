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

	lst.i = 0;
	lst.error = 0;
	lst.on = 0;
	lst.remove = 0;
	lst.space_front = 0;
	lst.s = NULL;
	lst.space_back = 0;
	while (str[lst.i] != '\0')
	{
		if (str[lst.i] == '\'')
		{
			lst.i += 1;
			while (str[lst.i] != '\'' && str[lst.i] != '\0')
				lst.i += 1;
			if (str[lst.i] == '\'')
				lst.i += 1;
		}
		else if (str[lst.i] == '"')
		{
			lst.i += 1;
			while (str[lst.i] != '"' && str[lst.i] != '\0')
				lst.i += 1;
			if (str[lst.i] == '"')
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

int	counts_dollar_escape(char *str)
{
	int i;
	int count;
	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\\' && str[i + 1] == '\\')
		{
			count += 1;
			i += 2;
		}
		else
		{
			count += 1;
			i += 1;
		}
	}
	return (count);
}

char	*remove_dollar_escape(char *s)
{
	int i;
	int j;
	char *ss;
	i = 0;
	j = 0;
	ss = (char *) malloc(sizeof (char ) * counts_dollar_escape(s) + 1);
	if (ss == NULL)
		return NULL;
	while (s[i] != '\0')
	{
		if (s[i] == '\\' && s[i + 1] == '\\')
		{
			ss[j] = s[i];
			i += 2;
			j += 1;
		}
		else
		{
			ss[j] = s[i];
			i += 1;
			j += 1;
		}
	}
	ss[j] = '\0';
	return (ss);
}
