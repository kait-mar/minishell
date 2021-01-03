/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molabhai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 16:19:20 by molabhai          #+#    #+#             */
/*   Updated: 2020/12/24 11:56:13 by molabhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"
//int     check_meta(char *s)

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
	int j;
	int on;

	i = 0;
	j = 0;
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

t_export		*check_export(char **splits, char **env)
{
	int i;
	int	j;
	t_export	*export;
	int			on;

	on = 0;
	j = 0;
	if (!(export = (t_export *) malloc(sizeof(t_export))))
		return (NULL);
	ft_memset(export, 0, sizeof(t_export));
	i = 1;
	export->command = ft_strdup(splits[0]);
	if (!(export->argument = (char **) ft_calloc(sizeof(char *), arguments_in(splits, i) + 1)))
		return (NULL);
	if (how_mutch_arguments(splits, i) == 1)
	{
		while (splits[i] != NULL)
		{
			splits[i] = ft_strtrim(splits[i], "\t");
			if (check_double_quote(splits[i]) == 1)
				splits[i] = without_that(splits[i], '\"');
			else if (check_quote(splits[i]) == 1)
				splits[i] = without_that(splits[i], '\'');
			if (check_exp_lex(splits[i]) == 1)
			{
				export->argument[j] = ft_strdup(splits[i]);
				j += 1;
				export->flag = 1;
			}
			else
				export->flag = 0;
			i += 1;
		}
	}
	else
	{
		i = 0;
		if (!(export->env = (char **) ft_calloc(sizeof(char *),(arguments_in(env, i) + 1))))
			return (NULL);
		while (env[i])
		{
			export->env[i] = front_append(env[i], "declare -x ");
			i += 1;
		}
		export->flag = 2;
	}
	return (export);
}

void	export_command(char **env, char *str, int *status)
{	
	t_export *export;
	int		i;
	int		j;
	int 	stop;
	char	**splits;

	i = 0;
	j = 0;
	stop = 0;
	splits = take_only_carac(str);
	export = check_export(splits, env);
	if (export->flag == 1)
	{
		while (export->argument[j] != NULL)
		{
			while (env[i] != NULL)
			{
				if (match(env[i], export->argument[j]) == 1)
				{
					env[i] = ft_strdup(export->argument[j]);
					stop = 1;
				}
				i += 1;
			}
			if (env[i] == NULL &&  stop == 0)
			{
				env[i] = ft_strdup(export->argument[j]);
				env[i + 1] = NULL;
			}
			j += 1;
			i = 0;
			stop = 0;
		}
		*status = 0;
	}
	else if (export->flag == 2)
	{
		while (export->env[i])
		{		
			ft_printf("%s\n", export->env[i]);
			i += 1;
		}
		*status = 0;
	}
	else
	{
		ft_printf("Error in export command\n");
		*status = 1;
	}
	free_splits(splits);
	free_export(export);
}

void	env_command(char **env, t_meta *meta, int *status)
{
	int i;

	i = 0;
 	if (ft_strncmp(meta->argument, "", ft_strlen(meta->argument)) != 0)
	{
		while (meta != NULL)
		{
			meta->argument = ft_strtrim(meta->argument, "\t");
			if (check_env(meta->argument) == 1)
			{
				ft_printf("Command [%s] doesnt exist\n", meta->argument);
				*status = 127;
				return ;
			}
			meta = meta->next;
		}
	}
	while (env[i])
	{
		ft_printf("%s\n", env[i]);
		i += 1;
	}
	*status = 0;
}
