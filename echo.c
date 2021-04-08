#include "minishell.h"
#include <stdio.h>

int	echo(char *argv, char **env, int *status)
{
	char	**bult;
	int		i;
	int		b;
	char	**split;
	char	**str;
	int		spaces;

	i = 0;
	spaces = 0;
	argv = skip_first_word(&argv);
	if (ft_strcmp(argv, "") == 0)
	{
        my_putchar('\n');
        *status = 0;
		return (0);
	}
	argv = ft_strtrim(argv, "\t");
	bult = keep_split(argv, 39, 34);
	int k = 0;
	b = 0;
	while (*bult != NULL)
	{
		if (find(*bult, 39) == 0 && find(*bult, 34) == 0)
		{
			str = ft_split(*bult, ' ');
			if (*str == NULL)
				break;
			while (*str)
			{
				if (flag_strcmp(*str, "-n") == 0)
				{
					str++;
					i = 1;
					*bult = skip_first_word(&(*bult));
				}
				else
				{
					b = 1;
					break;
				}
			}
			if (b == 1)
				break;
			else if (**bult == '\0')
				bult++;

		}
		else
            break ;
	}
	put_cases(bult, env, status);
	if (i == 0)
        my_putchar('\n');
	*status = 0;
	return (0);
}
