#include "../minishell.h"
#include <stdio.h>

void	my_putchar(char c)
{
	write(1, &c, 1);
}

int	last_put_condition(char **bult, int which_quote)
{
	return ((find_without(bult[g_global.j_echo], '$') == 0
			&& find_without(bult[g_global.j_echo], '"') == 0
			&& find_without(bult[g_global.j_echo], '\'') == 0)
		|| which_quote == 39);
}

void	to_free(char **bult)
{
	int	i;

	i = 0;
	while (bult[i])
	{
		free(bult[i]);
		i++;
	}
	free(bult);
}

void	flags(char **bult, int *i)
{
	while (bult[g_global.j_echo] != NULL)
	{
		if (find(bult[g_global.j_echo], 39) == 0
			&& find(bult[g_global.j_echo], 34) == 0)
		{
			if (check_echo_flag(bult, i) == 0)
				break ;
		}
		else
			break ;
	}
}

int	echo(char *argv, char **env, int *status)
{
	char	**bult;
	int		i;
	char	*s;

	i = 0;
	g_global.j_echo = 0;
	argv = skip_first_word(argv);
	if (ft_strcmp(argv, "") == 0)
	{
		my_putchar('\n');
		*status = 0;
		free(argv);
		return (0);
	}
	s = argv;
	argv = ft_strtrim(argv, "\t");
	free(s);
	bult = keep_split(argv, 39, 34);
	flags(bult, &i);
	echo_complet(bult, env, status, i);
	to_free(bult);
	free(argv);
	return (0);
}
