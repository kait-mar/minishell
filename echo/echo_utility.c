#include "../minishell.h"


int	print_env(char *bult, char **env, int which_quote, int *status)
{
	int		i;

	i = 0;
	while (*bult)
	{
		if (*bult == '\\' && *(bult + 1) == '\\')
			bult = print_env1(bult);
		if (*bult == '\\' && (*(bult + 1) == '$' || *(bult + 1) == '"' || *(bult + 1) == '\''))
		{
			bult++;
			my_putchar(*(bult++));
		}
		while (print_env_condition(bult) == 1)
			my_putchar(*(bult++));
		if (*bult == '\\' && (*(bult + 1) == '\\' || *(bult + 1) == '$'))
			continue;
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

	j = how_many_escape(*bult);
	if (j % 2 != 0)
	{
		while (*(*bult + 1) == '\\')
			(*bult)++;
	}
	else
	{
		while (**bult == '\\')
			(*bult)++;
	}
	j /= 2;
	while (--j >= 0)
		ft_putchar('\\');
	return (bult);
}

char	**put_cases1(char **bult)
{
	while (**bult != '\0')
	{
		if (**bult == '\\' && (*(*bult + 1) == '$' || *(*bult + 1) == '"'
			|| *(*bult + 1) == '\'' || *(*bult + 1) == '\\'))
			bult = put_cases2(bult);
		if (**bult == '\\' && (*(*bult + 1) == '$'
			|| *(*bult + 1) == '"' || *(*bult + 1) == '\''))
			(*bult)++;
		else if (**bult == '\\')
		{
			my_putchar(**bult);
			(*bult)++;
		}
		while (**bult != '\0' && **bult != '\\')
		{
			my_putchar(**bult);
			(*bult)++;
		}
	}
	return (bult);
}

void	put_cases(char **bult, char **env, int *status)
{
	char	**split;
	int		i;

	i = 0;
	while (*bult)
	{
		if (find(*bult, 39) == 0 && find(*bult, 34) == 0)
			print(bult, env, status);
		else if (find_how_many(*bult, 39) == 2 &&
				find_how_many(*bult, 34) == 2 && find(*bult, '$') == 0)
		{
			if (**bult == '\'')
				*bult = ft_strtrim(*bult, "'");
			else
				*bult = ft_strtrim(*bult, "\"");
			ft_putstr(*bult);
		}
		else if (find_how_many(*bult, 39) == 2 && find_how_many(*bult, 34) == 2)
			*bult = in_between_cases(*bult, env, status);
		else if (find(*bult, 39) == 1 || find(*bult, 34) == 1)
			last_put_cases(bult, env, status, &i);
		bult++;
	}
}
