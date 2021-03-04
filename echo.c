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

int		only_star(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '*' && s[i] != '\0')
		i++;
	if ((s[i] == '*' && (s[i + 1] == ' ' || s[i + 1] == '\0' || s[i + 1] == '\t')) ||
		(s[i] == '*' && (s[i - 1] == ' ' || s[i - 1] == '\0' || s[i - 1] == '\t')))
		return (1);
	else
		return (0);
}

int		print(char **bult, char **env, int *status)
{
	int		j;
	char	**tab;
	int		i;
	int		fd;

	i = 0;
	if (only_star(*bult) == 1)
		stream_directory();
	while ((**bult != '$' || (**bult == '\\' && *(*bult + 1) == '$')) && **bult != '\0')
	{
		if (**bult == '\\' && *(*bult + 1) == '\\')
		{
			j = how_many_escape(*bult);
			if (j % 2 != 0)
			{
				while (*(*bult + 1) == '\\')
				(*bult)++;
			}
			else
			{
				while (**bult == '\\')
					(*bult)++;
			}
			j /= 2;
			while (--j >= 0)
				ft_putchar('\\');
			continue ;
		}
		else if (**bult == '\\' && *(*bult + 1) == '$')
			(*bult)++;
		else if (**bult == '\\' && *(*bult + 1) == '\0')
		{
			(*bult)++;
			return (1);
		}
		else if (**bult == '\\')
		{
			(*bult)++;
			continue ;
		}
        my_putchar(**bult);
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
        my_putchar(**bult);
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
            my_putchar(**bult);
			(*bult)++;
		}
	}
	//ft_printf("\nit returned %d\n", i);
	return (i);
}

int		find(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c && (i == 0 || (i - 1 >= 0 && str[i - 1] != '\\')))
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
	if (*str[i] != '\0')
	{
		while ((*str)[i] != ' ' && (*str)[i] != '\t' && (*str)[i] != '\0')
			i++;
		while (((*str)[i] == ' ' || (*str)[i] == '\t') && (*str)[i] != '\0')
			i++;
		s = malloc(ft_strlen(*str) - i + 1);
		while ((*str)[i] != '\0')
			s[j++] = (*str)[i++];
		s[j] = '\0';
		if (*str)
			free(*str);
		//printf("Here Skip \n");
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
	//ft_printf("the argv is %s\n", argv);
	argv = skip_first_word(&argv);
	if (ft_strcmp(argv, "") == 0)
	{
        my_putchar('\n');
		return (0);
	}
	argv = ft_strtrim(argv, " ");
	argv = ft_strtrim(argv, "\t");
	bult = keep_split(argv, 39, 34);
	int k = 0;
	//while (bult[k] != NULL)
	//	ft_printf("|%s|\n", bult[k++]);
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
	if (i == 0)
        my_putchar('\n');
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
		if (*s1 != '\0' && *s2 != '\0' && (*s1 == *s2 || *s1 == *s2 - 32))
		{
			s1++;
			s2++;
		}
		else
			break ;
	}
	if (*s1 != *s2)
	{
	//	printf("echo returned %d\n", (unsigned char)*s1 - (unsigned char)*s2);
		return ((unsigned char)*s1 - (unsigned char)*s2);
	}
	else
	{
	//	printf("echo returned 0\n");
		return (0);
	}
}