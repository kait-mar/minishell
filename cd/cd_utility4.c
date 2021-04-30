/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utility4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kait-mar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 15:19:19 by kait-mar          #+#    #+#             */
/*   Updated: 2021/04/15 15:19:22 by kait-mar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int     check_only_single_double(char *s)
{
    int i;

    i = 0;
    if (s[i] == '\'' && s[i + 1] == '\'')
        return (1);
    else if (s[i] == '\"' && s[i + 1] == '\"')
        return (1);
    return (0);
}

void	new_pwd(char **env, char *str)
{
	int i;
	int k;
	static int	res = 0;
	char *old_pwd;

	i = 0;
	k = 0;
	old_pwd = add_in("PWD=", str);
	if (g_global.pwd_only)
		free(g_global.pwd_only);
	g_global.pwd_only = ft_strdup(old_pwd);
	while (env[i])
	{
		if (find_pwd(env[i]) == 1)
		{
			if (res >= 1)
				free(env[i]);
			env[i] = ft_strdup(old_pwd);
			res += 1;
			k = 1;
			break ;
		}
		i += 1;
	}
	if (env[i] == NULL && k == 0 && g_global.pwd_on == 0)
	{
		env[i] = ft_strdup(old_pwd);
		env[i + 1] = NULL;
	}
	if (old_pwd)
		free(old_pwd);
}

char	*old_pwd_helper(char **env, int i)
{
	int		j;
	char	*take_it;
	char	*old_pwd;
	char	*s;

	j = 0;
	 while (env[j])
    {
        if (find_pwd(env[j]) == 1)
        {
        	s = ft_strdup(env[j]);
            take_it = only_after_equal(s);
            free(s);
            i = 1;
            break ;
        }
        j += 1;
    }
    if (i == 0 && g_global.pwd_on == 0)
		old_pwd = old_pwd_support();
    else if (i == 1)
        old_pwd = add_in("OLDPWD=", take_it);
    else
        old_pwd = add_in("OLDPWD=", "");
    if (g_global.oldpwd_only)
    	free(g_global.oldpwd_only);
    g_global.oldpwd_only = ft_strdup(old_pwd);
    free(take_it);
    take_it = NULL;
	return (old_pwd);
}

char	*old_pwd_support()
{
	char	*old_pwd;
	char 	*s;

	old_pwd = (char *) ft_calloc(1, 100);
	if (old_pwd == NULL)
		return (NULL);
	if (getcwd(old_pwd, 100) == NULL)
		ft_printf("%s\n", strerror(errno));
	s = add_in("OLDPWD=", old_pwd);
	free(old_pwd);
	old_pwd = NULL;
	return (s);
}

void    old_pwd(char **env)
{
    char *old_pwd;
    int i;
    int k;
    static int res = 0;

    i = 0;
    k = 0;
   old_pwd = old_pwd_helper(env, i);
    while (env[i])
    {
        if (find_old_pwd(env[i]) == 1)
        {
        	if (res >= 1)
        		free(env[i]);
            env[i] = ft_strdup(old_pwd);
			k = 1;
			res += 1;
			break ;
        }
        i += 1;
    }
    if (env[i] == NULL && k == 0)
    {
		env[i] = ft_strdup(old_pwd);
		env[i + 1] = NULL;
	}
    free(old_pwd);
    old_pwd = NULL;
}
