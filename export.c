/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molabhai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 16:19:20 by molabhai          #+#    #+#             */
/*   Updated: 2020/12/07 14:38:06 by molabhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"


int		check_quote(char *str)
{
	int i;
	int on;

	 i = 0;
	 on = 0;
	 while (str[i] != '\0')
	 {
		 if (str[i] == '\'')
			 on = 1;
		 i += 1;
	 }
	 return (on);
}

int		check_double_quote(char *str)
{
	int i;
	int on;

	 i = 0;
	 on = 0;
	 while (str[i] != '\0')
	 {
		 if (str[i] == '\"')
			 on = 1;
		 i += 1;
	 }
	 return (on);
}

int		check_env(char *str)
{
	char *s;
	int i;
	int on;

	i = 0;
	on = 0;
	s = "env";
	if (check_quote(str) == 1)
		str = without_that(str, '\'');
	else if (check_double_quote(str) == 1)
		str = without_that(str, '\"');
	if (check_quote(str) == 0 && check_double_quote(str) == 0)
	{
		str = ft_toStrLower(str);
		while (i < 3)
		{
			if (str[i] != s[i])
				on = 1;
			i += 1;
		}
		if (ft_isalpha(str[i]))
			on = 1;
		return (on);
	}
	else
		on = 1;
	return (on);
}

t_export		*check_export(char **splits)
{
	int i;
	t_export	*export;
	int			on;

	on = 0;
	if (!(export = (t_export *) malloc(sizeof(t_export))))
		return (NULL);
	memset(export, 0, sizeof(t_export));
	i = 1;
	export->command = ft_strdup(splits[0]);
	if (how_mutch_arguments(splits, i) == 1)
	{
		while (splits[i] != NULL)
		{
			splits[i] = ft_strtrim(splits[i], "\t");
			if (check_exp_lex(splits[i]) == 1)
			{
				export->argument = ft_strdup(splits[i]);
				export->flag = 1;
			}
			i += 1;
		}
	}
	return (export);
}

void	export_command(char **env, char **splits)
{	
	t_export *export;
	int		i;

	i = 0;
	export = check_export(splits);
	if (export->flag == 1)
	{
		while (env[i] != NULL)
			i += 1;
		if (env[i] == NULL)
			env[i] = ft_strdup(export->argument);
		env[i + 1] = NULL;
	}
	else
		ft_printf("Error in export command\n");
}

void	env_command(char **env, char **splits)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (splits[j] != NULL)
	{
		splits[j] = ft_strtrim(splits[j], "\t");
		if (check_env(splits[j]) == 1)
		{
			ft_printf("Command [%s] doesnt exist\n", splits[j]);
			return ;
		}
		j += 1;
	}
	while (env[i])
	{
		ft_printf("%s\n", env[i]);
		i += 1;
	}
}
