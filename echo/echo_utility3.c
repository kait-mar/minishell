#include "../minishell.h"

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

int	homogene(char *s)
{
	int	i;
	int	sq;
	int	dq;

	i = 0;
	sq = 0;
	dq = 0;
	while (s[i])
	{
		if (s[i] == '\'')
			sq = '\'';
		else if (s[i] == '"')
			dq = '"';
		i++;
	}
	if (sq == 0 || dq == 0)
		return (1);
	return (0);
}

int	flag_strcmp(char *s1)
{
	int	i;

	i = 0;
	if (echo_strcmp(s1, "-n") == 0)
		return (0);
	if (*s1 == '\'')
		s1 = ft_strtrim(s1, "'");
	else if (*s1 == '"')
		s1 = ft_strtrim(s1, "\"");
	if (s1[i] == '-')
		i++;
	else
		return (1);
	while (s1[i] != '\0' && s1[i] == 'n')
		i++;
	if (s1[i] == '\0')
		return (0);
	return (1);
}

int	echo_strcmp(char *s1, char *s2)
{
	if (s1 == 0 || s2 == 0)
		return (0);
	if (homogene(s1) == 0)
		return (1);
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

int	find(char *str, char c)
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
