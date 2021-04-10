#include "../minishell.h"
#include <stdio.h>

void			my_putchar(char c)
{
    write(1, &c, 1);
}

int	echo(char *argv, char **env, int *status)
{
	char	**bult;
	int		i;

	i = 0;
	argv = skip_first_word(&argv);
	if (ft_strcmp(argv, "") == 0)
	{
        my_putchar('\n');
        *status = 0;
		return (0);
	}
	argv = ft_strtrim(argv, "\t");
	bult = keep_split(argv, 39, 34);
	while (*bult != NULL)
	{
		if (find(*bult, 39) == 0 && find(*bult, 34) == 0)
		{
			if (check_echo_flag(bult, &i) == 0)
				break ;
		}
		else
            break ;
	}
	echo_complet(bult, env, status, i);
	return (0);
}
