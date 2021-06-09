#include "../minishell.h"

int	how_many_escape(char *bult)
{
	int	i;

	i = 0;
	while (*bult != '\0' && *bult != '\\')
		bult++;
	while (*bult != '\0' && *bult == '\\')
	{
		bult++;
		i++;
	}
	return (i);
}

int	find_dollar_esacpe(char *bult)
{
	int	i;

	i = 0;
	while (bult[i] != '\0')
	{
		if (bult[i + 1] != '\0' && bult[i] == '\\' && bult[i + 1] == '$')
			return (1);
		i++;
	}
	return (0);
}

int	find_without(char *bult, char c)
{
	int	i;

	i = 0;
	while (bult[i] != '\0')
	{
		if (bult[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*trim_once(char *s)
{
	char	*str;
	int		i;
	int		j;

	if (s == NULL)
		return (NULL);
	str = malloc(ft_strlen(s) - 1);
	i = 1;
	j = 0;
	while (s[i + 1] != '\0')
	{
		str[j++] = s[i++];
	}
	str[j] = '\0';
	return (str);
}

char	*trim_once_left(char *s)
{
	char	*str;
	int		i;
	int		j;

	if (s == NULL)
		return (NULL);
	if (*s == ' ')
	{
		str = malloc(ft_strlen(s));
		s++;
	}
	else
		str = malloc(ft_strlen(s) + 1);
	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		str[j++] = s[i++];
	}
	str[j] = '\0';
	return (str);
}
