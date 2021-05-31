#include "../minishell.h"

char	*realloc_input(char *str, int string_len, t_sign lst)
{
	int	j;

	lst.len_after = 0;
	lst.len_before = 0;
	lst.len_cmd = ft_strlen(lst.s);
	j = 0;
	lst = realloc_list(str, lst);
	lst = realloc_list_support(str, lst, &j);
	lst.len_before = string_len;
	if (ft_strlen(lst.s) == 0)
	{
		if (str[lst.len_before] == ' ')
			lst.len_before += 1;
	}
	while (lst.len_after > 0)
	{
		lst.string[lst.i] = str[lst.len_before];
		lst.len_after--;
		lst.i += 1;
		lst.len_before += 1;
	}
	lst.string[lst.i] = '\0';
	free(str);
	return (lst.string);
}

t_sign	realloc_list(char *str, t_sign lst)
{
	int	o;

	o = 0;
	while (o < lst.i && str[o] != '\0')
	{
		lst.len_before += 1;
		o += 1;
	}
	o += (lst.j);
	while (str[o] != '\0')
	{
		lst.len_after += 1;
		o += 1;
	}
	lst.string = (char *) ft_calloc(sizeof (char),
			(lst.len_cmd + lst.len_after + lst.len_before) + 1);
	if (lst.string == NULL)
	{
		lst.error = -1;
		return (lst);
	}
	return (lst);
}

t_sign	realloc_list_support(char *str, t_sign lst, int *j)
{
	lst.i = 0;
	while (lst.len_before > 0)
	{
		lst.string[lst.i] = str[lst.i];
		lst.i += 1;
		lst.len_before--;
	}
	while (lst.len_cmd >= 0 && lst.s[*j] != '\0')
	{
		lst.string[lst.i] = lst.s[*j];
		lst.i += 1;
		*j += 1;
		lst.len_cmd--;
	}
	return (lst);
}
