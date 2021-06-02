/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executable_support4.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molabhai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 14:50:38 by molabhai          #+#    #+#             */
/*   Updated: 2021/04/17 14:50:40 by molabhai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	filling_string(char **tabs, char **env, char **str, char **string)
{
	int	j;
	int	i;

	j = 0;
	i = 0;
	while (env[j])
	{
		tabs = ft_split(env[j], '=');
		if (ft_strcmp(tabs[0], take_first_word(str[0] + 1)) == 0)
		{
			*string = ft_strjoin(*string, tabs[1]);
			i = 1;
			break ;
		}
		j++;
	}
	return (i);
}

int	wich_quote_func(char **env, char **string, char *bult, int which_quote)
{
	char	**str;
	char	**tabs;
	int		i;

	i = 0;
	str = NULL;
	tabs = NULL;
	if (which_quote == 0)
		str = ft_split(bult, ' ');
	else if (which_quote == 1)
	{
		str = ft_split(bult, ' ');
		if (str != NULL)
		{
			str = ft_split(str[0], '\'');
			if (str != NULL)
				str = ft_split(str[0], '"');
		}
	}
	if (*str != NULL)
		i = filling_string(tabs, env, str, string);
	return (i);
}

void	final_func(char *bult, char **string)
{
	char	*t;

	t = malloc(2);
	if (*bult == '$' && *(bult + 1) != '\0')
	{
		bult++;
		while (ft_isalnum(*bult) == 1 && *bult)
			bult++;
		while (*bult)
		{
			*t = *(bult++);
			t[1] = '\0';
			*string = ft_strjoin(*string, t);
		}
	}
}

char	*print_env_loop(char *bult, char **string, int which_quote)
{
	if (*bult == '\\' && *(bult + 1) == '\\')
		bult = first_return(bult, string);
	if (*bult == '\\' && (*(bult + 1) == '$'
			  || *(bult + 1) == '"' || *(bult + 1) == '\''))
		bult = second_return(bult, string);
	while (*bult != '$' && *bult != '\0'
		   && (*bult != '\\' || *(bult + 1) != '\\') && (*bult != '\\'
			|| *(bult + 1) != '$') && (*bult != '\\' || *(bult + 1) != '\'')
		   && (*bult != '\\' || *(bult + 1) != '"'))
		bult = third_return(bult, string);
	if (*bult == '\\' && (*(bult + 1) == '\\' || *(bult + 1) == '$'))
		return (bult);
	if ((*bult == '$' && ((which_quote == 0
					&& (*(bult + 1) == '\0' || *(bult + 1) == ' '))
				|| (which_quote == 1 && (*(bult + 1) == 39
						|| *(bult + 1) == 34 || *(bult + 1) == '\0'
						|| *(bult + 1) == ' ')))))
		bult = forth_return(bult, string);
	return (bult);
}

char	*parsed_func1(char **bult, char *str)
{
	if (**bult == '\'')
		*bult = ft_strtrim(*bult, "'");
	else
		*bult = ft_strtrim(*bult, "\"");
	str = ft_strjoin(str, *bult);
	return (str);
}
