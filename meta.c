/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meta.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kait-mar <kait-mar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 15:33:43 by molabhai          #+#    #+#             */
/*   Updated: 2021/01/02 10:24:14 by kait-mar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	until_meta(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
    {
        if (str[i] == '"')
        {
            i += 1;
            while (str[i] != '\0' && str[i] != '"')
            {
                i += 1;
            }
            if (str[i] == '"')
                i += 1;
        }
        if (str[i] == '\'')
        {
            i += 1;
            while (str[i] != '\0' && str[i] != '\'')
                i += 1;
            if (str[i] == '\'')
                i += 1;
        }
        if ((str[i] == '|' || str[i] == '>' || str[i] == '<' || str[i] == ';') && active(str, i) == 1)
            return (i);
        i += 1;
    }
	return (i);
}

void	free_meta_struct(t_meta *meta)
{
	free(meta->argument);
	free(meta);
}

int     valid(char *str, int j, int len)
{
    char *s;
    int i;

    s = from_to(str, j, len + 1);
    i = check_wich_command(str);
    if (i == 4)
    {
        while (j < len + 1)
        {
            if (check_single_double_quote(str[j]) == 1)
                return (1);
            j += 1;
        }
    }
    return (0);
}

int     count_meta(char *str)
{
    int  i;
    int     count;
    int     how_mutch;

    i = 0;
    how_mutch = 0;
    count = 0;
    while (str[i] != '\0')
    {
    	if (skip_quote(str, &i))
			continue;
        else if (str[i] == '\\')
        	count = return_count_meta(str, &i, count, &how_mutch);
        else if (str[i] == '|' || str[i] == '<' || str[i] == '>' || str[i] == ';')
        {
            count += 1;
            i += 1;
        }
        else
            i += 1;
    }
    return (count);
}

char	**splits_by_meta(char *str, int *meta)
{
	int	i;
	int	j;
	int	k;
	char	**splits;

	i = 0;
	j = 0;
	k = 0;
	splits = (char **) ft_calloc(sizeof(char *), count_meta(str) + 2);
	if (str == NULL)
		return (NULL);
	while (str[i] != '\0')
	{
		if (skip_quote(str, &i))
			continue;
        else if ((str[i] == ';' || str[i] == '|'
			|| str[i] == '<' || str[i] == '>') && (active(str, i) == 1))
        	splits[k++] = filling_split(str, &i, &j);
		else
			i += 1;
	}
	splits[k++] = from_to(str, j, i);
	return (splits);
}

int     check_append(char *s)
{
    int i;

    i = 0;
    while (s[i] != '\0')
    {
        if (s[i] == '>' && s[i + 1] == '>')
            return (TRUE);
        i += 1;
    }
    return (FALSE);
}

int     backslash_on(char *s)
{
    int i;
    int count;

    i = 0;
    count = 0;
    while (s[i] != '\0')
    {
        if (s[i] == '\\')
        {
            if (check_escape_meta(s, i) == 1)
            {
                while (s[i] == '\\')
                {
                    i += 1;
                    count += 1;
                }
                if ((count % 2) == 0)
                    return (1);
            }
        }
        i += 1;
    }
    return (0);
}

char    *removing_backslash(char *s)
{
    int i;
    int j;
    char *str;

    if (!(str = (char *) ft_calloc(sizeof (char ), ft_strlen(s) + 1)))
        return (NULL);
    i = 0;
    j = 0;
    while (s[i] != '\0')
    {

        i += 1;
    }
    str[j] = '\0';
    return (str);
}

t_meta	*split_it_all(char *str, char **env)
{
	t_meta	*global;
	char	**splits;
	int		i;
	int j;
	int		check;

	i = 0;
	j = 0;
	check = 0;
	if (!(global = (t_meta *) malloc(sizeof(t_meta))))
		return (NULL);
	splits = splits_by_meta(str, &check);
	if (splits[i] == NULL)
        return NULL;
    global->command = check_wich_command(take_first_word(splits[i]));
	if (splits == NULL)
		return (NULL);
	global = split_it_all_loop(splits, global, i);
	return (global);
}