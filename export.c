/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kait-mar <kait-mar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 16:19:20 by molabhai          #+#    #+#             */
/*   Updated: 2021/01/02 18:31:06 by kait-mar         ###   ########.fr       */
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


void    export_realloc(void)
{
    t_export *tmp;
    int     i;

    if (!(tmp = (t_export *) malloc(sizeof (t_export))))
        return ;
    i = 0;
    if (!(tmp->saver = (char **) ft_calloc(sizeof (char *), arguments_in(g_export->saver, i) + 1)))
        return ;
    while (g_export->saver[i])
    {
        tmp->saver[i] = ft_strdup(g_export->saver[i]);
        i += 1;
    }
    if (!(g_export = (t_export *) malloc(sizeof (t_export))))
        return ;
    i = 0;
    if (!(g_export->saver = (char **) ft_calloc(sizeof (char *), arguments_in(tmp->saver, i) + 2)))
        return ;
    while (tmp->saver[i])
    {
        g_export->saver[i] = ft_strdup(tmp->saver[i]);
        i += 1;
    }
    i = 0;
    while (tmp->saver[i])
    {
        free(tmp->saver[i]);
        tmp->saver[i] = NULL;
        i += 1;
    }
    free(tmp);
    tmp = NULL;
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

t_export		*check_export(char **splits, char **env, t_export *export)
{
	int i;
	int k;
	int	j;
	int			on;

	on = 0;
	j = 0;
	k = 0;
    i = 1;
	if (export == NULL)
    {
        if (!(export = (t_export *) malloc(sizeof(t_export))))
            return (NULL);
        if (!(export->argument = (char **) ft_calloc(sizeof(char *), arguments_in(splits, i) + 1)))
            return (NULL);
    }
	export->command = ft_strdup(splits[0]);
	export->flag = 0;
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
			if(ft_isalpha(splits[i][0]))
			{
                k = 0;
                export_realloc();
                while (g_export->saver[k])
                    k += 1;
                g_export->saver[k] = ft_strdup(splits[i]);
                g_export->saver[k + 1] = NULL;
                if (export->flag == 0)
                    export->flag = 3;
            }
			else
            {
			    ft_printf("bash: export: '%s': not a valid identifier\n", splits[i]);
                export->flag = 0;
            }
			i += 1;
		}
	}
	else
	{
		i = 0;
		if (!(export->env = (char **) ft_calloc(sizeof(char *),(arguments_in(g_export->saver, i) + 1))))
			return (NULL);
		while (g_export->saver[i])
		{
			export->env[i] = front_append(g_export->saver[i], "declare -x ");
			export->env[i][ft_strlen(export->env[i]) + 1] = '\0';
			i += 1;
		}
		export->flag = 2;
	}
	return (export);
}

void 	export_command(char **env, char *str, int *status, t_export *export)
{	
	int		i;
	int		j;
	int 	stop;
	char	**splits;

	i = 0;
	j = 0;
	stop = 0;
	splits = take_only_carac(str);
	export = check_export(splits, env, export);
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
			if (env[i] == NULL && stop == 0)
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
}

void 	env_command(char **env, t_meta *meta, int *status)
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