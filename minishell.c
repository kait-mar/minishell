#include "minishell.h"
#include <stdio.h>

void	ft_putstr(char *s)
{
	if (s == NULL)
		return ;
	while (*s != '\0')
	{
		write(1, &(*s), 1);
		s++;
	}
}

void	print(char **bult, char **env)
{
	int		j;
	char	**tab;
	int		i;

	if (**bult == '$')
	{
		j = 0;
		i = 0;
		while (env[j])
		{
			tab = ft_split(env[j], '=');
			if (ft_strcmp(tab[0], (*bult) + 1) == 0)
			{
				ft_putstr(tab[1]);
				i = 1;
				break ;
			}
			j++;
		}
		if (i == 1)
			(*bult)++;
		else
			ft_putstr(*bult);
	}
	else
		ft_putstr(*bult);
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

int		find(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	char	*line;
	char	**bult;
	int		i;

	i = 0;
	get_next_line(0, &line);
	//line = "echo hello world";
	bult = ft_split(line, ' ');
	if (ft_strcmp(bult[0], "echo") == 0)
	{
		bult++;
		if (ft_strcmp(*bult, "-n") == 0)
		{
			bult++;
			i = 1;
		}
		if (find(line, '<') == 0 && find(line, '>') == 0 && find(line, '>>') == 0)
		{
			while (*(bult + 1) != NULL)
			{
				print(bult, env);
				write(1, " ", 1);
				bult++;
			}
			print(bult, env);
		}
		if (i == 0)
			ft_putchar('\n');
	}
	return (0);
}
