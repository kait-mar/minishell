#include <stdio.h>
#include <stdlib.h>
int        coun(char *s, char c)
{
    int        i;
    int        count;
    int        k;

    i = 0;
    count = 0;
    while (s[i] != '\0')
    {
        k = 0;
        while (s[i] != c && s[i] != '\0')
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
    }
    return (count);
}

char    **keep_split(char *s, char c)
{
	int			i;
	int			j;
	int			k;
	int			l;
	char		**tab;

	if (!s)
		return (NULL);
	i = 0;
	j = 0;
    int count = coun(s, c);
	if (!(tab = (char **)malloc(sizeof(*tab) * (count + 1))))
		return (NULL);
	while (s[i] != '\0' && j < count)
	{
		k = 0;
		while (s[i] != c && s[i] != '\0')
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
			while (s[i] != c && s[i] != '\0')
			{
				tab[j][k++] = s[i++];
			}
			tab[j][k] = '\0';
		}
        else if (s[i] == c)
		{
			i++;
			k++;
			while (s[i] != c && s[i] != '\0')
			{
				i++;
				k++;
			}
			if (s[i] == c)
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

int main()
{
  char *s = "'-n ' hello 'world'    here 'we go   !'yes";
  //int i = coun(s, 39);
  //printf("%d\n", i);
  char **line = keep_split(s, 39);
  int i =0;
  while (line[i])
    printf("|%s|\n", line[i++]);
  return 0;
}
