/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meta.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molabhai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 15:33:43 by molabhai          #+#    #+#             */
/*   Updated: 2020/12/26 14:54:19 by molabhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	until_meta(char *str)
{
	int i;

	i = 0;
	while ((str[i] != ';' || str[i] != '<' || str[i] != '>' ||
				(str[i]  != '>' && str[i + 1] != '>')) && str[i] != '\0')
		i += 1;
	return (i);
}

/*
static char		*skip_word(char	*str)
{
	int	 i;

	i = 0;
	while 
}*/

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
		if (str[i] == ';' || str[i] == '|'
			|| str[i] == '<' || str[i] == '>')
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

char	**splits_by_meta(char	*str, int *meta)
{
	int	i;
	int	j;
	int	k;	
	char	**splits;

	i = 0;
	j = 0;
	k = 0;
	splits = (char **) ft_calloc(sizeof(char *) , 1000);
	if (str == NULL)
	{
		splits[k++] = ft_strdup(" ");
		return (NULL);
	}
	while (str[i] != '\0')
	{
		if (str[i] == ';' || str[i] == '|'
			|| str[i] == '<' || str[i] == '>')
		{
			splits[k++] = from_to(str, j, i + 1);
			i = i + 1;
			j = i;
			*meta = 1;
		}
		else
			i += 1;
	}
	splits[k++] = from_to(str, j, i);
	return (splits);
}

t_meta	*split_it_all(char *str)
{
	t_meta	*global;
	t_meta	*temp;
	char	**splits;
	char	*s;
	int		i;
	int		check;

	i = 0;
	check = 0;
	if (!(global = (t_meta *) malloc(sizeof(t_meta))))
		return (NULL);
	splits = splits_by_meta(str, &check);
    global->command = check_wich_command(take_first_word(splits[i]));
	if (splits == NULL)
		return (NULL);
	s = ft_substr(splits[i], 0, until_meta(splits[i])); 
	if (check_meta(s) == TRUE)
	{
		s = ft_substr(splits[i], 0, until_meta(splits[i]) - 1);
		global->meta = splits[i][until_meta(splits[i]) - 1];
		if (s != NULL)
		{
            if (global->command != 0&& global->command != 4 && global->command !=  6)
                global->argument = skip_first_word(&s);
            else if (global->command == 0 || global->command == 4 || global->command == 6)
                global->argument = ft_strdup(s);
        }
	}
	else if (check_meta(s) == FALSE)
	{
		global->meta = 0;
		if (s != NULL)
        {
		    if (global->command != 0&& global->command != 4 && global->command !=  6)
                global->argument = skip_first_word(&s);
		    else if (global->command == 0 || global->command == 4 || global->command == 6)

		        global->argument = ft_strdup(s);
        }
	}
	global->next = NULL;
	i += 1;
	while (splits[i])
	{
		if (!(temp = (t_meta *) malloc(sizeof(t_meta))))
			return (NULL);
		temp->command = check_wich_command(take_first_word(splits[i]));
		s = ft_substr(splits[i], 0 , until_meta(splits[i])); 
		if (check_meta(s) == TRUE)
		{
			s = ft_substr(splits[i], 0, until_meta(splits[i]) - 1);
			temp->meta = splits[i][until_meta(splits[i]) - 1];
			if (s != NULL)
            {
			    if (temp->command != 0 && temp->command != 4 && temp->command !=  6)
                    temp->argument = skip_first_word(&s);
			    else if (temp->command == 0 || temp->command == 4 || temp->command == 6)
			        temp->argument = ft_strdup(s);
            }
		}
		else if (check_meta(s) == FALSE)
		{
			temp->meta = 0;
			if (s != NULL)
            {
			    if (temp->command != 0 && temp->command != 4 && temp->command !=  6)
                    temp->argument = skip_first_word(&s);
                else if (temp->command == 0 || temp->command == 4 || temp->command == 6)
                    temp->argument = ft_strdup(s);
            }
		}
		temp->next = NULL;
		ft_lstadd(&global, temp);
		i += 1;
	}
	return (global);
}
