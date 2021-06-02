#include "../minishell.h"

int	print_env(char *bult, char **env, int which_quote, int *status)
{
	int		i;

	i = 0;
	while (*bult)
	{
		if (*bult == '\\' && *(bult + 1) == '\\')
			bult = print_env1(bult);
		if (*bult == '\\' && (*(bult + 1) == '$'
				|| *(bult + 1) == '"' || *(bult + 1) == '\''))
		{
			bult++;
			my_putchar(*(bult++));
		}
		while (print_env_condition(bult) == 1)
			my_putchar(*(bult++));
		if (*bult == '\\' && (*(bult + 1) == '\\' || *(bult + 1) == '$'))
			continue ;
		if (which_quote_condition(bult, which_quote) == 1)
			my_putchar(*(bult++));
		if (*bult == '\0')
			break ;
		else
			bult = last_print_env_case(bult, env, which_quote, status);
	}
	return (i);
}

char	**put_cases2(char **bult)
{
	int	j;
	int	k;

	k = 0;
	j = how_many_escape(bult[g_global.j_echo]);
	if (j % 2 != 0)
	{
		while (bult[g_global.j_echo][k] == '\\')
			k++;
	}
	else
	{
		while (bult[g_global.j_echo][k] == '\\')
			k++;
	}
	j /= 2;
	while (--j >= 0)
		ft_putchar('\\');
	return (bult);
}

char	**put_cases1(char **bult)
{
	int	k;

	k = 0;
	if (g_global.e_quote == 1)
	{
		bult[g_global.j_echo] = es_for_quote(bult[g_global.j_echo]);
		g_global.e_quote = 0;
	}
	while (bult[g_global.j_echo][k] != '\0')
	{
		if (condition2(bult, k))
			k++;
		else if (bult[g_global.j_echo][k] == '\\')
		{
			my_putchar(bult[g_global.j_echo][k]);
			k++;
		}
		while (bult[g_global.j_echo][k] != '\0'
			&& bult[g_global.j_echo][k] != '\\')
		{
			my_putchar(bult[g_global.j_echo][k]);
			k++;
		}
	}
	return (bult);
}

void	put_cases(char **bult, char **env, int *status)
{
	int		i;

	i = 0;
	while (bult[g_global.j_echo])
	{
		if (find(bult[g_global.j_echo], 39) == 0
			&& find(bult[g_global.j_echo], 34) == 0)
			print(bult, status);
		else if (find_how_many(bult[g_global.j_echo], 39) == 2
			&& find_how_many(bult[g_global.j_echo], 34) == 2
			&& find(bult[g_global.j_echo], '$') == 0)
			bult = put_cases_norminette(bult);
		else if (find_how_many(bult[g_global.j_echo], 39) == 2
			&& find_how_many(bult[g_global.j_echo], 34) == 2)
			bult[g_global.j_echo]
				= in_between_cases(bult[g_global.j_echo], env, status);
		else if (find(bult[g_global.j_echo], 39) == 1
			|| find(bult[g_global.j_echo], 34) == 1)
			last_put_cases(bult, env, status, &i);
		g_global.j_echo++;
	}
}

char	**put_cases_norminette(char **bult)
{
	char	*s;

	if (bult[g_global.j_echo][0] == '\'')
	{
		s = bult[g_global.j_echo];
		bult[g_global.j_echo] = ft_strtrim(bult[g_global.j_echo], "'");
		free(s);
	}
	else
	{
		s = bult[g_global.j_echo];
		bult[g_global.j_echo] = ft_strtrim(bult[g_global.j_echo], "\"");
		free(s);
	}
	ft_putstr(bult[g_global.j_echo]);
	return (bult);
}
