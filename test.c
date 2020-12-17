#include <stdio.h>
#include <stdlib.h>
#include "Libft/libft.h"

int		coun(char *s, char c)
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
		tab[j] = malloc(k + 1);
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
			tab[j] = malloc(k + 1);
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

static int	fct(char s, char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == s)
			return (1);
		i++;
	}
	return (0);
}

static char	*other_return(char const *s1, char const *set)
{
	if (s1 == NULL)
		return (NULL);
	else if (set == NULL)
		return ((char *)s1);
	else
		return ((char *)set);
}

static char	*return_vr(int end, int start)
{
	char	*vr;

	if (end < start)
	{
		vr = malloc(1);
		if (vr == 0)
			return (0);
		vr[0] = '\0';
		return (vr);
	}
	else
		return (NULL);
}

char		*ft_strtrim_left(char const *s1, char const *set)
{
	int		start;
	int		end;
	char	*str;

	if (s1 == NULL || set == NULL)
		return (other_return(s1, set));
	start = 0;
	end = ft_strlen(s1) - 1;
	while (fct(s1[start], (char *)set) != 0)
		start++;
	//while (fct(s1[end], (char *)set) != 0 && end > 0)
	//	end--;
	if (end < start)
		return (return_vr(end, start));
	str = (char *)malloc(end - start + 2);
	if (str == NULL)
		return (NULL);
	ft_memcpy(str, s1 + start, end - start + 1);
	str[end - start + 1] = '\0';
	return (str);
}

int main()
{
  //char *s = "'-n '    hello 'world'    here 'we go   !'yes";
  //char **line = keep_split(s, 39);
  //int i =0;
  //while (line[i])
   // printf("|%s|\n", line[i++]);
   char	*str = "   hello world  ";
   printf("|%s|\n", ft_strtrim_left(str, " "));
  return 0;
}


/*t_spaces	*keep_split(char *s, char c, char b)
{
	int			i;
	int			j;
	int			k;
	int			l;
	t_spaces	*list;

	if (!s)
		return (NULL);
	i = 0;
	j = 0;
	int count = coun(s, c, b);
	if (!(list = (char **)malloc(sizeof(t_spaces) * (count + 1))))
		return (NULL);
	while (s[i] != '\0' && j < count)
	{
		k = 0;
		while (s[i] != c && s[i] != b && s[i] != '\0')
		{
			i++;
			k++;
		}
		if (k != 0)
		{
			if (!(list[j].bult = malloc(k + 1)))
				return (ft_tofree(list, j));
			i -= k;
			k = 0;
			while (s[i] != c && s[i] != b && s[i] != '\0')
			{
				list[j].bult[k++] = s[i++];
			}
			list[j].bult[k] = '\0';
		}
		else if (s[i] == c || s[i] == b)
		{
			i++;
			k++;
			while (s[i] != c && s[i] != b && s[i] != '\0')
			{
				i++;
				k++;
			}
			if (s[i] == c || s[i] == b)
			{
				i++;
				k++;
			}
			if (!(list[j].bult = malloc(k + 1)))
				return (ft_tofree(list, j));
			i -= k;
			l = k;
			k = 0;
			while (k < l)
				list[j].bult[k++] = s[i++];
			list[j].bult[k] = '\0';
		}
		j++;
	}
	list[j].bult = NULL;
	return (list);
}*/