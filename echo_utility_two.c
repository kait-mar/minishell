#include "minishell.h"

int		find_how_many(char *s, char c)
{
	int	i;

	i = 0;
	while (*s)
	{
		if (*s == c)
			i++;
		s++;
	}
	return (i);
}

char	*take_first_word(char *s)
{
	char	*string;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (ft_isalnum(s[i]) && s[i])
		i++;
	if (!(string = malloc(i + 1)))
		return (0);
	i = 0;
	while (s[i] && (s[i] == ' ' || s[i] == '\t'))
		i++;
	while (ft_isalnum(s[i]) && s[i])
	{
		string[j++] = s[i++];
	//	i++;
	}
	string[j] = '\0';
	return (string);
}
