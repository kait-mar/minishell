/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_sign_support3.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molabhai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 18:29:29 by molabhai          #+#    #+#             */
/*   Updated: 2021/06/02 18:29:31 by molabhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*string_oldpwd(int *on)
{
	char	*string;

	string = NULL;
	if (g_global.check == 0)
		string = ft_strdup("");
	else
	{
		string = ft_strdup(g_global.oldpwd_only);
		string = take_after_equal(string);
		*on = 1;
	}
	return (string);
}

char	*string_pwd(int *on)
{
	char	*string;

	string = NULL;
	string = ft_strdup(g_global.pwd_only);
	string = take_after_equal(string);
	*on = 1;
	return (string);
}

char	*string_frees(char *string, int escape, char *ss, int on)
{
	char	*string_free;

	if (escape > 0)
	{
		if (on == 1)
		{
			string_free = string;
			string = adding_escape(string, escape);
			free(string_free);
		}
		else
		{
			string_free = string;
			string = adding_escape(ss, escape);
			free(string_free);
		}
	}
	return (string);
}

t_sign	change_valid_norminette(t_sign lst, char *str)
{
	if (escape_front_true(str, lst.i) == 1
		&& lst.space_front == 1 && inside_quotes(str, lst.i) == 1)
		lst.s = add_front_space(lst.s);
	if (escape_back_true(str, lst.i) == 1 && lst.space_back == 1)
		lst.s = add_back_space(lst.s);
	else if ((str[lst.i + lst.j] == '$' && lst.space_back == 1))
		lst.s = add_back_space(lst.s);
	return (lst);
}
