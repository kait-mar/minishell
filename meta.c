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
	    if (str[i] == ';' && str[i - 1] != '\\')
	        return (i + 1);
        if (str[i] == '>'&& str[i - 1] != '\\')
        {
            if (str[i + 1] == '>')
                return (i + 2);
            else
                return (i + 1);
        }
        if (str[i] == '<' && str[i - 1] != '\\')
            return (i + 1);
        if (str[i] == '|' && str[i - 1] != '\\')
            return (i + 1);
        i += 1;
    }
	return (i);
}

void	ft_lstadd(t_meta **alst, t_meta *new)
{
	t_meta *lst;

	if (*alst == NULL)
		*alst = new;
	else
	{
		lst = *alst;
		while (lst->next)
			lst = lst->next;
		lst->next = new;
	}
}

static	int		check_meta(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if ((str[i] == ';' || str[i] == '|'
            			|| str[i] == '<' || str[i] == '>') && str[i - 1] != '\\')
			return (TRUE);
		i += 1;
	}
	return (FALSE);
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

char	**splits_by_meta(char *str, int *meta)
{
	int	i;
	int	j;
	int	k;
	int len;
	char	**splits;

	i = 0;
	j = 0;
	k = 0;
	len = 0;
	splits = (char **) ft_calloc(sizeof(char *) , 1000);
	if (str == NULL)
	{
		splits[k++] = ft_strdup(" ");
		return (NULL);
	}
	while (str[i] != '\0')
	{
		if ((str[i] == ';' || str[i] == '|'
			|| str[i] == '<' || str[i] == '>') && (str[i - 1] != '\\'))
		{
		    if (str[i + 1] == '>' && str[i] == '>')
            {
		        if (valid(str, j, i) == 0)
                    splits[k++] = from_to(str, j, i + 2);
		        else
                {
		            while (str[i] != '\"')
		                i += 1;
                    splits[k++] = from_to(str, j, i + 2);
                }
               i += 2;
            }
		    else
            {
                if (valid(str, j, i) == 0)
                    splits[k++] = from_to(str, j, i + 2);
                else
                {
                    while (str[i] != '\"')
                        i += 1;
                    splits[k++] = from_to(str, j, i + 1);
                }
                i = i + 1;
            }
			j = i;
			*meta = 1;
		}
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

    i = 0;
    while (s[i] != '\0')
    {
        if (s[i] == '\\')
            return (1);
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
        if (s[i] != '\\')
        {
            str[j] = s[i];
            j += 1;
        }
        i += 1;
    }
    str[j] = '\0';
    return (str);
}

t_meta	*split_it_all(char *str)
{
	t_meta	*global;
	t_meta	*temp;
	t_buffer *buffer;
	char	**splits;
	char	*s;
	int		i;
	int j;
	int		check;
	int on;

	i = 0;
	j = 0;
	check = 0;
	on = 0;
	if (!(global = (t_meta *) malloc(sizeof(t_meta))))
		return (NULL);
	splits = splits_by_meta(str, &check);
	if (splits[i] == NULL)
        return NULL;
    global->command = check_wich_command(take_first_word(splits[i]));
	if (splits == NULL)
		return (NULL);
	if (check_wich_command(splits[i]) == 4)
    {
	    while (splits[i][j] != '\0')
        {
	        if (check_single_double_quote(splits[i][j]) == 1)
            {
	            on = 1;
                break ;
            }
	        j += 1;
        }
    }
	if (on == 1)
	    s = ft_strdup(splits[i]);
	else
    	s = ft_substr(splits[i], 0, until_meta(splits[i]));
	if (backslash_on(s) == 1)
	    s = removing_backslash(s);
    if (check_meta(s) == TRUE && backslash_on(splits[i]) == 0)
	{
        if (check_append(s) == TRUE)
        {
            s = ft_substr(splits[i], 0, until_meta(splits[i]) - 2);
            global->meta_append = 1;
        }
        else if (check_append(s) == FALSE)
        {
            global->meta_append = 0;
            if (on == 1)
                s = ft_strdup(splits[i]);
            else
                s = ft_substr(splits[i], 0, until_meta(splits[i]) - 1);
        }
        if (on == 1)
            global->meta = 0;
        else
            global->meta = splits[i][until_meta(splits[i]) - 1];
		if (s != NULL)
		{
            if (global->command != 0 && global->command != 6)
            {
                global->argument = skip_first_word(&s);
                global->argument = ft_strtrim(global->argument, " ");
                global->argument = ft_strtrim(global->argument, "\t");
            }
            else if (global->command == 0 || global->command == 6)
            {
                global->argument = ft_strdup(s);
                global->argument = ft_strtrim(global->argument, " ");
                global->argument = ft_strtrim(global->argument, "\t");
            }
        }
	}
	else if (check_meta(s) == FALSE || backslash_on(splits[i]) == 1)
	{
		global->meta = 0;
		if (s != NULL)
        {
		    if (global->command != 0 && global->command !=  6)
            {
                global->argument = skip_first_word(&s);
                global->argument = ft_strtrim(global->argument, " ");
                global->argument = ft_strtrim(global->argument, "\t");
            }
		    else if (global->command == 0 || global->command == 6)
                global->argument = ft_strdup(s);
        }
		global->meta_append = 0;
	}
	global->next = NULL;
	i += 1;
	while (splits[i])
	{
        if (check_wich_command(splits[i]) == 4)
        {
            while (splits[i][j] != '\0')
            {
                if (check_single_double_quote(splits[i][j]) == 1)
                {
                    on = 1;
                    break ;
                }
                j += 1;
            }
        }
        if (on == 1)
            s = ft_strdup(splits[i]);
        else
            s = ft_substr(splits[i], 0, until_meta(splits[i]));
		if (!(temp = (t_meta *) malloc(sizeof(t_meta))))
			return (NULL);
		temp->command = check_wich_command(take_first_word(splits[i]));
		s = ft_substr(splits[i], 0 , until_meta(splits[i]));
        if (backslash_on(s) == 1)
            s = removing_backslash(s);
		if (check_meta(s) == TRUE &&  backslash_on(splits[i]) == 0)
		{
            if (check_append(s) == TRUE)
            {
                s = ft_substr(splits[i], 0, until_meta(splits[i]) - 2);
                temp->meta_append = 1;
            }
            else if (check_append(s) == FALSE)
            {
                temp->meta_append = 0;
                if (on == 1)
                    s = ft_strdup(splits[i]);
                else
                    s = ft_substr(splits[i], 0, until_meta(splits[i]) - 1);
                on = 0;
            }
            if (on == 1)
                temp->meta = 0;
            else
                temp->meta = splits[i][until_meta(splits[i]) - 1];
			if (s != NULL)
            {
			    if (temp->command != 0 && temp->command != 4 && temp->command !=  6) {
                    temp->argument = skip_first_word(&s);
                    temp->argument = ft_strtrim(temp->argument, " ");
                    temp->argument = ft_strtrim(temp->argument, "\t");
                }
			    else if (temp->command == 0 || temp->command == 4 || temp->command == 6)
                {
                    temp->argument = ft_strdup(s);
                    temp->argument = ft_strtrim(temp->argument, " ");
                    temp->argument = ft_strtrim(temp->argument, "\t");
                }
            }
		}
		else if (check_meta(s) == FALSE ||  backslash_on(splits[i]) == 1)
		{
			temp->meta = 0;
			if (s != NULL)
            {
			    if (temp->command != 0 && temp->command != 4 && temp->command !=  6)
                {
                    temp->argument = skip_first_word(&s);
                    temp->argument = ft_strtrim(temp->argument, " ");
                    temp->argument = ft_strtrim(temp->argument, "\t");
                }
                else if (temp->command == 0 || temp->command == 4 || temp->command == 6)
                {
                    temp->argument = ft_strdup(s);
                    temp->argument = ft_strtrim(temp->argument, " ");
                    temp->argument = ft_strtrim(temp->argument, "\t");
                }
            }
			temp->meta_append = 0;
		}
		temp->next = NULL;
		ft_lstadd(&global, temp);
		i += 1;
	}
	return (global);
}