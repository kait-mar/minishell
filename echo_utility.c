#include "minishell.h"

void	print_env(char *bult, char **env, int which_quote)
{
	char	**str;
	int		j;
	char	**tab;
	int		i;

	while (*bult)
	{
		while (*bult != '$')
			ft_putchar(*(bult++));
		str = ft_split(bult, ' ');
		i = 0;
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
		//if (i == 0)
		//	ft_putstr(str[0]);
		if (*bult == '$')
		{
			bult++;
			while (ft_isalnum(*bult) == 1)
				bult++;
		}
	}
}
