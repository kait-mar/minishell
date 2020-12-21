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
		if ((*bult == '$' && (*(bult + 1) == '\0' || *(bult + 1) == ' ') && (which_quote == 0 || (which_quote == 1 || *(bult  + 1) == 39 || *(bult  + 1) == 34))))
			ft_putchar(*(bult++));
		else
		{
			if (which_quote == 0)
				str = ft_split(bult, ' ');
			else if (which_quote == 1)
			{
				str = ft_split(bult , ' ');
				str = ft_split(str[0], '\'');
				str = ft_split(str[0], '"');
			}
			if (*str != NULL)
			{
				j = 0;
				while (env[j])
				{
					tab = ft_split(env[j], '=');
					if (ft_strcmp(tab[0], str[0] + 1) == 0)
					{
						ft_putstr(tab[1]);
						i = 1;
						break ;
					}
					j++;
				}
			}
			if (*bult == '$' && *(bult + 1) != '\0')
			{
				bult++;
				while (ft_isalnum(*bult) == 1)
					bult++;
			}
		}
	}
	return (i);
}

void	put_cases(char **bult, char **env)
{
	int		which_quote;
	char	**split;
	int		i;
	int		spaces;

	i = 0;
	spaces = 0;
	while (*bult)
	{
		if (find(*bult, 39) == 0 && find(*bult, 34) == 0)
		{
			split = ft_split(*bult, ' ');
			if (**bult == ' ')
				ft_putchar(' ');
			if (*split == NULL)
			{
				bult++;
				continue ;
			}
			if ((*bult)[ft_strlen(*bult) - 1] == ' ' && bult + 1 != NULL)
				spaces = 1;
			while (*(split + 1) != NULL)
			{
				if (print(split, env) == 1 || i == 1)
					write(1, " ", 1);
				split++;
			}
			print(split, env);
			if (spaces == 1)
				ft_putchar(' ');
			spaces = 0;
		}
		else if (find_how_many(*bult, 39) == 1 && find_how_many(*bult, 34) == 1 && find(*bult, '$') == 0)
		{
			if (**bult == '\'')
				*bult = ft_strtrim(*bult, "'");
			else
				*bult = ft_strtrim(*bult, "\"");
			ft_putstr(*bult);
		}
		else if (find_how_many(*bult, 39) == 1 && find_how_many(*bult, 34) == 1)
		{
			if (**bult == '\'')
				*bult = ft_strtrim(*bult, "'");
			else
				*bult = ft_strtrim(*bult, "\"");
			print_env(*bult, env, 1);
		}
		else if (find(*bult, 39) == 1 || find(*bult, 34) == 1)
		{
			if (**bult == 39)
			{
				*bult = ft_strtrim(*bult, "'");
				which_quote = 39;
			}
			else if (**bult == 34)
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
				i = 0;
			}
			else
			{
				if (print_env(*bult, env, 0) == 1)
					write(1, " ", 1);
			}
		}
		bult++;
	}
}

void	put_normal(char **split, char **env, int i)
{
	while (*(split + 1) != NULL)
	{
		if (print(split, env) == 1)
			write(1, " ", 1);
		split++;
	}
	print(split, env);
	if (i == 1)
		ft_putchar(' ');
}
