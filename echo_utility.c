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
