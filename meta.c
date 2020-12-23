/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meta.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molabhai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 15:33:43 by molabhai          #+#    #+#             */
/*   Updated: 2020/12/23 18:13:38 by molabhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "minishell.h"
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



char	**splits_by_meta(char	*str)
{
	int	i;
	int	j;
	int	k;	
	char	**splits;

	i = 0;
	j = 0;
	k = 0;
	splits = (char **) ft_calloc(sizeof(char *) , 1000);
	while (str[i] != '\0')
	{
		if (str[i] == ';' || str[i] == '|'
			|| str[i] == '<' || str[i] == '>')
		{
			splits[k++] = from_to(str, j, i + 1);
			 i = i + 1;
			 j = i;
		}
		else
			i += 1;
	}
	splits[k++] = from_to(str, j, i);
	if (splits[k] != NULL)
		splits[k] = NULL;
	return (splits);
}

t_meta	*split_it_all(char *str)
{
	t_meta	*global;
	t_meta	*temp;
	char	**splits;
	char	*s;
	int		i;

	i = 0;
	if (!(global = (t_meta *) malloc(sizeof(t_meta))))
		return (NULL);
	splits = splits_by_meta(str);
	s = ft_substr(splits[i], 0, ft_strlen(splits[i]) - 1);
	global->command = check_wich_command(take_first_word(splits[i]));
	global->argument = skip_first_word(&s);
	global->meta = splits[i][ft_strlen(splits[i]) - 1];
	global->next = NULL;
		printf("splits[i] == > %s\n", splits[i]);
	i += 1;
	while (splits[i])
	{
		if (!(temp = (t_meta *) malloc(sizeof(t_meta))))
			return (NULL);
		temp->command = check_wich_command(take_first_word(splits[i]));
		s = ft_substr(splits[i], 0, ft_strlen(splits[i]) - 1);
		if ((temp->meta = splits[i][ft_strlen(splits[i])]) == ';')
			s = ft_substr(splits[i], 0, ft_strlen(splits[i]) - 1);
		else
		{
			s = splits[i];
			temp->meta = 0;
		}
		temp->argument = skip_first_word(&s);
		temp->next = NULL;
		ft_lstadd(&global, temp);
		printf("splits[i] == > %s\n", splits[i]);
		i += 1;
	}
	return (global);
}
