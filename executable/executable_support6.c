/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executable_support6.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molabhai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 16:09:12 by molabhai          #+#    #+#             */
/*   Updated: 2021/04/17 16:09:26 by molabhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	parsing_loop(char **bult, char **str)
{
	while (**bult != '\0')
	{
		if (**bult == '\\' && (*(*bult + 1) == '$'
				|| *(*bult + 1) == '"' || *(*bult + 1) == '\''
				|| *(*bult + 1) == '\\'))
			*str = parsed_func4(bult, *str);
		if (**bult == '\\' && (*(*bult + 1) == '$'
				|| *(*bult + 1) == '"' || *(*bult + 1) == '\''))
			(*bult)++;
		else if (**bult == '\\')
			*str = parsed_func5(bult, *str);
		while (**bult != '\0' && **bult != '\\')
			*str = parsed_func6(bult, *str);
	}
}

void	parsing(char **bult, int which_quote, char **str, char **env)
{
	parsed_func3(bult, &which_quote);
	if ((find_without(*bult, '$') == 0 && find_without(*bult, '"') == 0
			&& find_without(*bult, '\'') == 0) || which_quote == 39)
	{
		if (find_without(*bult, '\\') == 0 || which_quote == 39)
			*str = ft_strjoin(*str, *bult);
		else
			parsing_loop(bult, str);
	}
	else
	{
		if ((print_env_two(*bult, env, 0, str)) == 1)
			write(1, " ", 1);
	}
}
