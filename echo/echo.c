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
	g_global.j_echo = 0;
	argv = skip_first_word(&argv);
	if (ft_strcmp(argv, "") == 0)
	{
        my_putchar('\n');
        *status = 0;
		return (0);
	}
	argv = ft_strtrim(argv, "\t");
	bult = keep_split(argv, 39, 34);
	/*int k = 0;
	while (bult[k])
	{
		ft_printf("[bult[]] is %s\n", bult[k++]);
	}*/
	while (bult[g_global.j_echo] != NULL)
	{
		if (find(bult[g_global.j_echo], 39) == 0 && find(bult[g_global.j_echo], 34) == 0)
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
