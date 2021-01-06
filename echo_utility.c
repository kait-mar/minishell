#include "minishell.h"

void			my_putchar(char c)
{
    if (g_piping == 0)
        write(1, &c, 1);
    else if (g_piping == 1)
    {
        write(g_fd[1],  &c, 1);
        printf("Here\n");
    }
}

int	print_env(char *bult, char **env, int which_quote, int *status)
{
	char	**str;
	int		j;
	char	**tab;
	int		i;

	i = 0;
	while (*bult)
	{
		while (*bult != '$' && *bult != '\0')
			my_putchar(*(bult++));
		if ((*bult == '$' && ((which_quote == 0 && (*(bult + 1) == '\0' || *(bult + 1) == ' ')) || (which_quote == 1 && (*(bult  + 1) == 39 || *(bult  + 1) == 34 || *(bult + 1) == '\0' || *(bult + 1) == ' ')))))
			my_putchar(*(bult++));
		if (*bult == '\0')
			break ;
		else
		{
			if (which_quote == 0)
				str = ft_split(bult, ' ');
			else if (which_quote == 1)
			{
				if (*(str = ft_split(bult, ' ')) != NULL)
				{
					if (*(str = ft_split(str[0], '\'')) != NULL)
						str = ft_split(str[0], '"');
				}
			}
			if (*str != NULL)
			{
				j = 0;
				while (env[j])
				{
					tab = ft_split(env[j], '=');
					if (ft_strcmp(tab[0], take_first_word(str[0] + 1)) == 0)
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
				while (ft_isalnum(*bult) == 1 && *bult)
					bult++;
				while (*bult)
				{
					my_putchar(*bult);
						bult++;
				}
			}
		}
	}
	return (i);
}

void	put_cases(char **bult, char **env, int *status)
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
				my_putchar(' ');
			if (*split == NULL)
			{
				bult++;
				continue ;
			}
			if ((*bult)[ft_strlen(*bult) - 1] == ' ' && bult + 1 != NULL)
				spaces = 1;
			while (*(split + 1) != NULL)
			{
				if (print(split, env, status) == 1 || i == 1)
					write(1, " ", 1);
				split++;
			}
			print(split, env, status);
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
				if (print_env(*bult, env, 0, status) == 1)
					write(1, " ", 1);
			}
		}
		bult++;
	}
}

void	put_normal(char **split, char **env, int i, int *status)
{
	while (*(split + 1) != NULL)
	{
		if (print(split, env, status) == 1)
			write(1, " ", 1);
		split++;
	}
	print(split, env, status);
	if (i == 1)
		my_putchar(' ');
}

