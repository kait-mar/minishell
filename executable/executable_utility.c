/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executable_utility.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molabhai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 15:20:39 by molabhai          #+#    #+#             */
/*   Updated: 2021/04/17 15:20:41 by molabhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	print_env_two(char *bult, char **env, int which_quote, char **string)
{
	int	i;

	i = 0;
	while (*bult)
	{
		bult = print_env_loop(bult, string, which_quote);
		if (*bult == '\0')
			break ;
		else
		{
			i = wich_quote_func(env, string, bult, which_quote);
			final_func(bult, string);
		}
	}
	return (i);
}

char	*return_parsed(char **bult, char **env)
{
	char	*str;
	int		which_quote;

	which_quote = 0;
	str = (char *) malloc(1);
	if (!(str))
		return (NULL);
	*str = '\0';
	while (*bult)
	{
		if (find(*bult, 39) == 0 && find(*bult, 34) == 0)
			str = ft_strjoin(str, *bult);
		else if (find_how_many(*bult, 39) == 2
			&& find_how_many(*bult, 34) == 2 && find(*bult, '$') == 0)
			parsed_func1(bult, str);
		else if (find_how_many(*bult, 39) == 2 && find_how_many(*bult, 34) == 2)
			parsed_func2(bult, &str, env);
		else if (find(*bult, 39) == 1 || find(*bult, 34) == 1)
			parsing(bult, which_quote, &str, env);
		bult++;
	}
	return (str);
}

int	check_bin_echo(char *str)
{
	if (ft_strncmp(str, "/bin/echo", ft_strlen("/bin/echo")) == 0
		&& str[ft_strlen("/bin/echo")] == ' ')
		return (1);
	return (0);
}
