#include "../minishell.h"

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
		k = count_helper1(s, &i, &count, &j);
		if (k == 1)
			continue ;
		k = 0;
		while (count_condition (s, i, c, b))
			increment_counters(&i, &k);
		if (k != 0)
			count++;
		else if (s[i] == c && s[i] != '\0')
			count_helper(s, c, &i, &count);
		else if (s[i] == b && s[i] != '\0')
			count_helper(s, b, &i, &count);
	}
	return (count);
}

char	**ft_tofree(char *tabs[], int j)
{
	while (--j > 0)
	{
		free(tabs[j]);
		tabs[j] = NULL;
	}
	free(tabs);
	tabs = NULL;
	return (NULL);
}

t_split	keep_split_initializer(void)
{
	t_split	lst;

	lst.i = 0;
	lst.j = 0;
	lst.check = -33;
	return (lst);
}

t_split	keep_split_support(t_split lst)
{
	lst.k = 0;
	return (lst);
}

char	**keep_split(char *s, char c, char b)
{
	t_split	lst;

	if (!s)
		return (NULL);
	lst = keep_split_initializer();
	lst.count = coun(s, c, b);
	if (lst.count == 0)
		lst.count = 1;
	lst.tabs = (char **)malloc(sizeof(*(lst.tabs)) * (lst.count + 1));
	if (lst.tabs == NULL)
		return (NULL);
	while (s[lst.i] != '\0' && lst.j < lst.count)
	{
		lst = keep_split_support(lst);
		if (lst.k == 1)
			continue ;
		lst.k = 0;
		lst = increment_counters2(s, lst, c, b);
		lst = keep_split_core(s, lst, c, b);
		if (lst.check == -1)
			return (NULL);
		(lst.j)++;
	}
	lst.tabs[lst.j] = NULL;
	return (lst.tabs);
}
