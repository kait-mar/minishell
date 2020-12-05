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

//re change here for the count espace for split 
/*int		*count_espace(char *s)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		if (s[i] != c && s[i] != '\0')
		{
			count++;
			i++;
		}
		while (s[i] != c && s[i] != '\0')
			i++;
	}
	return (count);
}*/

/*int		find(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}*/

int	echo(char **argv, char **env)
{
	char	*line;
	char	**bult;
	int		i;

	i = 0;
	get_next_line(0, &line);
	printf("my line char is : %s\n", line);
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
		if (find(line, '<') == 0 && find(line, '>') == 0)
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
