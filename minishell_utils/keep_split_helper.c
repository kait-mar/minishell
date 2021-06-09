#include "../minishell.h"

t_split	keep_split_support2(char *s, t_split lst, char c, char b)
{
	lst.tabs[lst.j] = malloc(lst.k + 1);
	if (lst.tabs[lst.j] == NULL)
	{
		lst.check = -1;
		ft_tofree(lst.tabs, lst.j);
		return (lst);
	}
	lst.i -= lst.k;
	lst.k = 0;
	while (((s[lst.i] != c && s[lst.i] != b)
			|| ((s[lst.i] == c || s[lst.i] == b)
				&& lst.i - 1 >= 0 && s[lst.i - 1] == '\\')) && s[lst.i] != '\0')
		lst.tabs[lst.j][(lst.k)++] = s[(lst.i)++];
	lst.tabs[lst.j][lst.k] = '\0';
	return (lst);
}

t_split	keep_split_support3(char *s, t_split lst, char c)
{
	(lst.i)++;
	(lst.k)++;
	while ((s[lst.i] != c
			|| (lst.i - 1 >= 0 && s[lst.i - 1] == '\\' && s[lst.i] == c))
		&& s[lst.i] != '\0')
	{
		(lst.i)++;
		(lst.k)++;
	}
	lst = keep_split_supporter(lst, c, s);
	lst.i -= lst.k;
	lst.l = lst.k;
	lst.k = 0;
	while (lst.k < lst.l)
		lst.tabs[lst.j][(lst.k)++] = s[(lst.i)++];
	lst.tabs[lst.j][lst.k] = '\0';
	return (lst);
}

t_split	keep_split_core(char *s, t_split lst, char c, char b)
{
	if (lst.k != 0)
	{
		lst = keep_split_support2(s, lst, c, b);
	}
	else if (s[lst.i] == c && (lst.i == 0
			|| (lst.i - 1 >= 0 && s[lst.i - 1] != '\\')))
	{
		lst = keep_split_support3(s, lst, c);
	}
	else if (s[lst.i] == b
		&& (lst.i == 0 || (lst.i - 1 >= 0 && s[lst.i - 1] != '\\')))
	{
		lst = keep_split_support3(s, lst, b);
	}
	return (lst);
}

t_split	increment_counters2(char *s, t_split lst, char c, char b)
{
	while (((s[lst.i] != c && s[lst.i] != b)
			|| ((s[lst.i] == c || s[lst.i] == b)
				&& lst.i - 1 >= 0 && s[lst.i - 1] == '\\'))
		&& s[lst.i] != '\0' )
	{
		(lst.i)++;
		(lst.k)++;
	}
	return (lst);
}
