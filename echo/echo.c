#include "../minishell.h"
#include <stdio.h>

void			my_putchar(char c)
{
    write(1, &c, 1);
}

void	to_free(char **bult)
{
	int	i;

	i = 0;
	while (bult[i])
	{
		//printf("the freed word in split is %s\n", bult[i]);
		free(bult[i]);
		i++;
	}
	free(bult);
}

int	echo(char *argv, char **env, int *status)
{
	char	**bult;
	int		i;
	char	*s;

	i = 0;
	g_global.j_echo = 0;
	//fprintf(stderr, "the argb is %s\n", argv);
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
	free(argv);
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
	to_free(bult);
	return (0);
}
