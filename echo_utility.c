#include "minishell.h"

int	print_env(char *bult, char **env, int which_quote)
{
	char	**str;
	int		j;
	char	**tab;
	int		i;

	i = 0;
	while (*bult)
	{
		while (*bult != '$' && *bult != '\0')
			ft_putchar(*(bult++));
		str = ft_split(bult, ' ');
		if (*str != NULL)
		{
			j = 0;
			while (env[j])
			{
				tab = ft_split(env[j], '=');
				if (ft_strcmp(tab[0], str[0]) == 0)
				{
					ft_putstr(tab[1]);
					i = 1;
					break ;
				}
				j++;
			}
		}
		if (*bult == '$')
		{
			bult++;
			while (ft_isalnum(*bult) == 1)
				bult++;
		}
	}
	return (i);
}

void	put_cases(char **bult, char **env)
{
	int		which_quote;
	char	**split;
	int		i;

	i = 0;
	while (*bult)
	{
		if (find(*bult, 39) == 0 && find(*bult, 34) == 0)
		{
			split = ft_split(*bult, ' ');
			while (*(split + 1) != NULL)
			{
				if (print(split, env) == 1 || i == 1)
					write(1, " ", 1);
				split++;
			}
			print(split, env);
		}
		else if (find(*bult, 39) == 1 || find(*bult, 34) == 1)
		{
			if (find(*bult, 39) == 1)
			{
				*bult = ft_strtrim(*bult, "'");
				which_quote = 39;
			}
			else
			{
				*bult = ft_strtrim(*bult, "\"");
				which_quote = 34;
			}
			//add the * case and / skip charactere
			if (find(*bult, '$') == 0 || which_quote == 39)
			{
				if (i == 1)
					write(1, " ", 1);
				ft_putstr(*bult);
				i = 1;
			}
			else
			{
				if (print_env(*bult, env, which_quote) == 1)
					write(1, " ", 1);
			}
		}
		bult++;
	}
}
