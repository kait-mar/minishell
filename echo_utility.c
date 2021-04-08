#include "minishell.h"

int	print_env(char *bult, char **env, int which_quote, int *status)
{
	char	**str;
	int		j;
	char	**tabs;
	int		i;

	i = 0;
	while (*bult) {
        if (*bult == '\\' && *(bult + 1) == '\\')
            bult = print_env1(bult);
        if (*bult == '\\' && (*(bult + 1) == '$' || *(bult + 1) == '"' || *(bult + 1) == '\'')) {
            bult++;
            my_putchar(*(bult++));
        }
        while (*bult != '$' && *bult != '\0' && (*bult != '\\' || *(bult + 1) != '\\') &&
               (*bult != '\\' || *(bult + 1) != '$') && (*bult != '\\' || *(bult + 1) != '\'') &&
               (*bult != '\\' || *(bult + 1) != '"')) {
            my_putchar(*(bult++));
        }
        if (*bult == '\\' && (*(bult + 1) == '\\' || *(bult + 1) == '$'))
            continue;
        if ((*bult == '$' && ((which_quote == 0 && (*(bult + 1) == '\0' || *(bult + 1) == ' '))
        || (which_quote == 1 && (*(bult + 1) == 39 || *(bult + 1) == 34 || *(bult + 1) == '\0'
        || *(bult + 1) == ' ')))))
            my_putchar(*(bult++));
        if (*bult == '\0')
            break;
        else {
            if (*bult == '$' && *(bult + 1) == '?') {
                ft_printf("%d", *status);
                bult = bult + 2;
            } else
                bult = print_env2(bult, env, which_quote, status);
        }
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
		if (**bult == '\\' && (*(*bult + 1) == '$' || *(*bult + 1) == '"' || *(*bult + 1) == '\'' || *(*bult + 1) == '\\'))
			bult = put_cases2(bult);
		if (**bult == '\\' && (*(*bult + 1) == '$' || *(*bult + 1) == '"' || *(*bult + 1) == '\''))
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
	int		which_quote;
	char	**split;
	int		i;
	int		spaces;
	int		j;

	i = 0;
	spaces = 0;
	while (*bult)
	{
		if (find(*bult, 39) == 0 && find(*bult, 34) == 0)
		{
			print(bult, env, status);
			if (spaces == 1)
				my_putchar(' ');
			spaces = 0;
		}
		else if (find_how_many(*bult, 39) == 2 && find_how_many(*bult, 34) == 2 && find(*bult, '$') == 0)
		{
			if (**bult == '\'')
				*bult = ft_strtrim(*bult, "'");
			else
				*bult = ft_strtrim(*bult, "\"");
			ft_putstr(*bult);
		}
		else if (find_how_many(*bult, 39) == 2 && find_how_many(*bult, 34) == 2)
		{
			if (**bult == '\'')
			{
					*bult = ft_strtrim(*bult, "'");
					ft_putstr(*bult);
			}
			else
			{
				*bult = ft_strtrim(*bult, "\"");
			print_env(*bult, env, 1, status);
			}
		}
		else if (find(*bult, 39) == 1 || find(*bult, 34) == 1)
		{
			if (**bult == 39)
			{
				*bult = trim_once(*bult);
				which_quote = 39;
			}
			else if (**bult == 34)
			{
				
				*bult = trim_once(*bult);
				which_quote = 34;
			}
			if ((find_without(*bult, '$') == 0 && find_without(*bult, '"') == 0 && find_without(*bult, '\'') == 0) || which_quote == 39)
			{
				if (find_without(*bult, '\\') == 0 || which_quote == 39)
				{
					if (i == 1)
						write(1, " ", 1);
					ft_putstr(*bult);
					i = 0;
				}
				else
					bult = put_cases1(bult);
			}
			else
			{
				if (print_env(*bult, env, 0, status) == 1)
					write(1, " ", 1);
			}
		}
		bult++;
	}
}
