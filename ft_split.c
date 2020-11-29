#include "minishell.h"

static int		coun(char *s, char c)
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
}

static int		len_mot(char *s, char c, int i)
{
	int	len;

	len = 0;
	while (s[i] != c && s[i] != '\0')
	{
		i++;
		len++;
	}
	return (len);
}

static char		**ft_tofree(char *tab[], int j)
{
	while (--j > 0)
		free(tab[j]);
	free(tab);
	return (NULL);
}

char			**ft_split(char const *s, char c)
{
	int			i;
	int			j;
	int			k;
	char		**tab;

	if (!s)
		return (NULL);
	i = 0;
	j = 0;
	if (!(tab = (char **)malloc(sizeof(*tab) * (coun((char *)s, c) + 1))))
		return (NULL);
	while (s[i] != '\0' && j < coun((char *)s, c))
	{
		k = 0;
		while (s[i] == c)
			i++;
		if (!(tab[j] = malloc(len_mot((char *)s, c, i) + 1)))
			return (ft_tofree(tab, j));
		while (s[i] != c && s[i] != '\0')
			tab[j][k++] = s[i++];
		tab[j][k] = '\0';
		j++;
	}
	tab[j] = NULL;
	return (tab);
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
