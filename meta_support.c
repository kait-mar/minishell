/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meta_support.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molabhai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 10:03:28 by molabhai          #+#    #+#             */
/*   Updated: 2021/04/10 10:03:30 by molabhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_meta(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if ((str[i] == ';' || str[i] == '|'
				|| str[i] == '<' || str[i] == '>') && active(str, i) == 1)
			return (TRUE);
		i += 1;
	}
	return (FALSE);
}

void	ft_lstadd(t_meta **alst, t_meta *new)
{
	t_meta	*lst;

	if (*alst == NULL)
	{
		*alst = new;
	}
	else
	{
		lst = *alst;
		while (lst->next)
			lst = lst->next;
//		if (lst->next == NULL)
//			lst->next = malloc(sizeof(t_meta));
//		lst->next->argument = ft_strdup(new->argument);
//		lst->next->meta = new->meta;
//		lst->next->command = new->command;
//		lst->next->meta_append = new->meta_append;
		lst->next = new;
		lst->next->next = NULL;
	}
}

t_meta	*split_it_all_loop(char **splits, t_meta *global, int i)
{
	t_meta	*temp;
	char	*s;
	char	*split_free;

	if (check_meta(splits[i]) == TRUE)
		global = meta_in(splits, global, &i);
	else if (check_meta(splits[i]) == FALSE)
		global = meta_out(splits, global, &i);
	global->next = NULL;
	while (splits[i])
	{
		temp = (t_meta *) malloc(sizeof(t_meta));
		temp->argument = NULL;
		if (temp == NULL)
			return (NULL);
		split_free = splits[i];
		splits[i] = remove_space(splits[i]);
		free(split_free);
		s = take_first_word(splits[i]);
		temp->command = check_wich_command(s);
		free(s);
		if (check_meta(splits[i]) == TRUE)
			temp = meta_in_between(splits, temp, &i);
		else if (check_meta(splits[i]) == FALSE)
			meta_out_between(splits, temp, &i);
		temp->next = NULL;
		ft_lstadd(&global, temp);
		//free_temp(temp);
		i += 1;
	}
	return (global);
}

int	skip_quote(char *str, int *i)
{
	int	on;

	on = 0;
	if (str[*i] == '"')
	{
		*i += 1;
		while (str[*i] != '\0' && str[*i] != '"')
			*i += 1;
		if (str[*i] == '"')
			*i += 1;
		on = 1;
	}
	else if (str[*i] == '\'')
	{
		*i += 1;
		while (str[*i] != '\0' && str[*i] != '\'')
			*i += 1;
		if (str[*i] == '\'')
			*i += 1;
		on = 1;
	}
	return (on);
}

char	*filling_split(char *str, int *i, int *j)
{
	char	*s;

	if (str[*i + 1] == '>' && str[*i] == '>')
	{
		if (valid(str, *j, *i) == 0)
			s = from_to(str, *j, *i + 2);
		else
			s = from_to(str, *j, *i + 2);
		*i += 2;
	}
	else
	{
		s = from_to(str, *j, *i + 1);
		*i += 1;
	}
	*j = *i;
	return (s);
}
