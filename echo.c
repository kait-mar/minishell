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

int		print(char **bult, char **env, int *status)
{
	int		j;
	char	**tab;
	int		i;
	int		fd;

	//Adde by The Hell
	fd = open("/Users/molabhai/Desktop/minishell/mini_file.txt",O_RDWR);
	//add a split here
	i = 0;
	while (**bult != '$' && **bult != '\0')
	{
		ft_putchar(**bult);
		ft_putchar_fd(**bult, fd);
		(*bult)++;
		i = 1;
	}
	if (**bult == '$' && *(*bult + 1) == '?')
	{
		ft_printf("%d", *status);
		*bult = *bult + 2;
	}
	else if (**bult == '$' && *(*bult + 1) == '\0')
	{
		ft_putchar(**bult);
		ft_putchar_fd(**bult, fd);
		return (1);
	}
	else if (**bult == '$' && *(*bult + 1) != '?')
	{
		j = 0;
		i = 0;
		while (env[j])
		{
			tab = ft_split(env[j], '=');
			if (ft_strcmp(tab[0], take_first_word((*bult) + 1)) == 0)
			{
				ft_putstr(tab[1]);
				ft_putstr_fd(tab[1], fd);
				i = 1;
				break ;
			}
			j++;
		}
		(*bult)++;
		while (ft_isalnum(**bult))
			(*bult)++;
		while (**bult)
		{
			ft_putchar(**bult);
			(*bult)++;
		}
	}
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
		s[j] = '\0';
		free(*str);
		return (s);
	}
	return (*str);
}

int	echo(char *argv, char **env, int *status)
{
	char	**bult;
	int		i;
	char	**split;
	char	**str;
	int		spaces;

	i = 0;
	spaces = 0;
	argv = skip_first_word(&argv);
	if (ft_strcmp(argv, "") == 0)
	{
		ft_putchar('\n');
		return (0);
	}
	argv = ft_strtrim(argv, " ");
	argv = ft_strtrim(argv, "\t");
	if (find(argv, '<') == 0 && find(argv, '>') == 0)
	{
		bult = keep_split(argv, 39, 34);
		if (find(*bult, 39) == 1 || find(*bult, 34) == 1)
		{
			if (ft_strcmp(*bult, "-n") == 0 || ft_strcmp(*bult, "'-n'") == 0 || ft_strcmp(*bult, "\"-n\"") == 0)
			{
				bult++;
				i = 1;
				*bult = ft_strtrim_left(*bult, " ");
			}
		}
		else
		{
			str = ft_split(*bult, ' ');
			if (ft_strcmp(*str, "-n") == 0)
			{
				str++;
				i = 1;
				*bult = skip_first_word(&(*bult));
			}
		}
		put_cases(bult, env, status);
	}
	if (i == 0)
		ft_putchar('\n');
	*status = 0;
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
	while (*s1 != '\0')
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
