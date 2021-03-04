#include "minishell.h"

static int	coun(char *s, char c, char b)
{
	int	i;
	int	count;
	int	k;
	int	j;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		k = 0;
		if (s[i] == '\\')
		{
			j = how_many_escape(s);
			if (j % 2 == 0)
			{
				count++;
				while (s[i] == '\\')
					i++;
				continue ;
			}
		}
		while (s[i] != '\0' &&
				((s[i] != c && s[i] != b) || ((s[i] == c || s[i] == b) && i - 1 >= 0 && s[i-1] == '\\')))
		{
			k++;
			i++;
		}
		if (k != 0)
			count++;
		else if (s[i] == c && s[i] != '\0')
		{
			i++;
			while (s[i] != c && s[i] != '\0')
				i++;
			if (s[i] == c)
				i++;
			count++;
		}
		else if (s[i] == b && s[i] != '\0')
		{
			i++;
			while (s[i] != b && s[i] != '\0')
				i++;
			if (s[i] == b)
				i++;
			count++;
		}
	}
	return (count);
}

static char		**ft_tofree(char *tab[], int j)
{
	while (--j > 0)
		free(tab[j]);
	free(tab);
	return (NULL);
}

char	**keep_split(char *s, char c, char b)
{
	int			i;
	int			j;
	int			k;
	int			l;
	int			esp;
	char		**tab;

	if (!s)
		return (NULL);
	i = 0;
	j = 0;
    int count = coun(s, c, b);
	if (!(tab = (char **)malloc(sizeof(*tab) * (count + 1))))
		return (NULL);
	while (s[i] != '\0' && j < count)
	{
		k = 0;
		if (s[i] == '\\')
		{
			esp = how_many_escape(s);
			if (esp % 2 == 0)
			{
				if (!(tab[j] = malloc(k + 1)))
					return (ft_tofree(tab, j));
				while (s[i] != '\0' && s[i] == '\\')
				{
					tab[j][k++] = s[i++];
				}
				s[i-1] = '\0';
				tab[j++][k] = '\0';
				continue ;
			}
		}
		while (((s[i] != c && s[i] != b) || ((s[i] == c || s[i] == b) && i - 1 >= 0 && s[i-1] == '\\')) && s[i] != '\0' )
		{
			i++;
			k++;
		}
		if (k != 0)
		{
			if (!(tab[j] = malloc(k + 1)))
				return (ft_tofree(tab, j));
			i -= k;
			k = 0;
		while (((s[i] != c && s[i] != b) || ((s[i] == c || s[i] == b) && i - 1 >= 0 && s[i-1] == '\\')) && s[i] != '\0' )
			{
				tab[j][k++] = s[i++];
			}
			tab[j][k] = '\0';
		}
        else if (s[i] == c && (i == 0 || (i-1 >= 0 && s[i-1] != '\\')))
		{
			i++;
			k++;
			while ((s[i] != c || (i-1 >=0 && s[i-1] == '\\' && s[i] == c)) && s[i] != '\0')
			{
				i++;
				k++;
			}
			if (s[i] == c && (i == 0 || (i-1 >= 0 && s[i-1] != '\\')))
			{
				i++;
				k++;
			}
			if (!(tab[j] = malloc(k + 1)))
				return (ft_tofree(tab, j));
			i -= k;
			l = k;
			k = 0;
			while (k < l)
				tab[j][k++] = s[i++];
			tab[j][k] = '\0';
		}
		else if (s[i] == b && (i == 0 || (i-1 >= 0 && s[i-1] != '\\')))
		{
			i++;
			k++;
			while ((s[i] != b || (i-1 >=0 && s[i-1] == '\\' && s[i] == b)) && s[i] != '\0')
			{
				i++;
				k++;
			}
			if (s[i] == b && (i == 0 || (i-1 >= 0 && s[i-1] != '\\')))
			{
				i++;
				k++;
			}
			if (!(tab[j] = malloc(k + 1)))
				return (ft_tofree(tab, j));
			i -= k;
			l = k;
			k = 0;
			while (k < l)
				tab[j][k++] = s[i++];
			tab[j][k] = '\0';
		}
		j++;
	}
	tab[j] = NULL;
	return (tab);
}
