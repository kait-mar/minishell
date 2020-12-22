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

	while (ft_isalnum(s[i]) && s[i])
		i++;
	if (!(string = malloc(i + 1)))
		return (0);
	i = 0;
	while (ft_isalnum(s[i]) && s[i])
	{
		string[i] = s[i];
		i++;
	}
	string[i] = '\0';
	return (string);
}
