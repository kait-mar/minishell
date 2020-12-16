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

int		print(char **bult, char **env)
{
	int		j;
	char	**tab;
	int		i;

	//add a split here
	i = 0;
	while (**bult != '$' && **bult != '\0')
	{
		ft_putchar(**bult);
		(*bult)++;
		i = 1;
	}
	if (**bult == '$' && *(*bult + 1) == '\0')
	{
		ft_putchar(**bult);
		return (1);
	}
	else if (**bult == '$')
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
		//if (i == 1)
			(*bult)++;
		//else
		//	ft_putstr(*bult);
	}
	//else
	//{
		//ft_putstr(*bult);
		//i = 1;
	//}
	return (i);
}

int		find(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void	quote_dquote(char *line)
{
	char	*str;

	str = malloc(2);
	*str = '"';
	str[1] = '\0';
	printf("the old line : %s\n", line);
	//add a free to line here
	line = ft_strtrim(line, str);
	printf("the new line : %s\n", line);
	ft_putstr(line);
}

char	*skip_first_word(char **str)
{
	char	*s;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (((*str)[i] == ' ' || (*str)[i] == '\t') && (*str)[i] != '\0')
		i++;
	if (str[i] != '\0')
	{
		while ((*str)[i] != ' ' && (*str)[i] != '\t' && (*str)[i] != '\0')
			i++;
		while (((*str)[i] == ' ' || (*str)[i] == '\t') && (*str)[i] != '\0')
			i++;
		s = malloc(ft_strlen(*str) - i + 1);
		while ((*str)[i] != '\0')
			s[j++] = (*str)[i++];
		(*str)[i] = '\0';
		free(*str);
		return (s);
	}
	return (*str);
}

int	echo(char *argv, char **env)
{
	char	**bult;
	int		i;
	char	**split;
	char	**str;

	i = 0;
	argv = skip_first_word(&argv);
	argv = ft_strtrim(argv, " ");
	argv = ft_strtrim(argv, "\t");
	if (find(argv, '<') == 0 && find(argv, '>') == 0)
	{
		bult = keep_split(argv, 39, 34);
		if (find(*bult, 39) == 1 || find(*bult, 34) == 1)
		{
			if (ft_strcmp(*bult, "-n") == 0 || ft_strcmp(*bult, "'-n'") == 0)
			{
				bult++;
				i = 1;
			}
		}
		else
		{
			str = ft_split(*bult, ' ');
			if (ft_strcmp(*str, "-n") == 0 || ft_strcmp(*str, "'-n'") == 0)
			{
				str++;
				i = 1;
			}
			put_cases(str, env);
		}
		put_cases(bult, env);
	}


	/*if (find(argv, '<') == 0 && find(argv, '>') == 0 && find(argv, 34)  == 0 && find(argv, 39) == 0)
	{
		while (*(bult + 1) != NULL)
		{
			print(bult, env);
			write(1, " ", 1);
			bult++;
		}
		print(bult, env);
	}
	else if (find(argv, 34)  == 1 || find(argv, 39)  == 1)
	{
		quote_dquote(argv);
	}*/
	if (i == 0)
		ft_putchar('\n');
	return (0);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	if (s1 == 0 || s2 == 0)
		return (0);
	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	if (s1[i] != s2[i])
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	else
		return (0);
}

int	echo_strcmp(const char *s1, const char *s2)
{
	if (s1 == 0 || s2 == 0)
		return (0);
	while (*s1 != '\0' && *s2 != '\0')
	{
		while ((*s1 == '\'' || *s1 == '\"') && *s1 != '\0')
			s1++;
		if (*s1 != '\0' && *s2 != '\0' && *s1 == *s2)
		{
			s1++;
			s2++;
		}
		else
			break ;
	}
	if (*s1 != *s2)
		return ((unsigned char)*s1 - (unsigned char)*s2);
	else
		return (0);
}