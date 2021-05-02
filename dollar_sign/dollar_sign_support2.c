#include "../minishell.h"

t_sign	change_valid(t_sign lst, char *str, char **env)
{
	if (inside_quotes(str, lst.i) == 1)
		lst.remove = 1;
	lst.s = chang_dollar(lst.s, env, &(lst.on));
	if ((lst.s)[0] == ' ')
		lst.space_front = 1;
	if (lst.s[ft_strlen(lst.s) - 1] == ' ')
		lst.space_back = 1;
	if (str[lst.i - 1] == '[' && str[lst.i + lst.j] == ']' && lst.remove == 1)
		lst.s = rm_space_variable(lst.s, 0);
	else if (str[lst.i - 1] == '[' && str[lst.i + lst.j] != ']' && lst.remove == 1)
		lst.s = rm_space_variable(lst.s, 1);
	else if (str[lst.i - 1] != '[' && str[lst.i + lst.j] == ']' && lst.remove == 1)
		lst.s = rm_space_variable(lst.s, 2);
	else if (lst.remove == 1)
		lst.s = remove_space(lst.s);
	if (escape_front_true(str, lst.i) == 1 && lst.space_front == 1 && inside_quotes(str, lst.i) == 1)
		lst.s = add_front_space(lst.s);
	if (escape_back_true(str, lst.i) == 1 && lst.space_back == 1)
		lst.s = add_back_space(lst.s);
	else if ((str[lst.i + lst.j] == '$' && lst.space_back == 1))
		lst.s = add_back_space(lst.s);
	return (lst);
}

t_sign	change_dollar_helper(t_sign lst, char **str, char **env)
{
	int	len;

	lst.j = dollar_len(*str, lst.i);
	lst.s = take_word(*str, lst.i, lst.j + lst.i);
	len = ft_strlen(lst.s);
	lst.valid = dollar_parsing(lst.s);
	lst.s = remove_escape_dollar(lst.s);
	lst.j = ft_strlen(lst.s);
	if (lst.valid == 1)
	{
		lst = change_valid(lst, *str, env);
	}
	*str = realloc_input(*str, lst.s, lst.j, len + lst.i, lst.i);
	//lst = realloc_input(*str, len + lst.i, lst);
	len = ft_strlen(lst.s);
	if (lst.s)
		free(lst.s);
	lst.i = len + lst.i;
	lst.remove = 0;
	return (lst);
}

t_sign	change_dollar_core(t_sign lst, char **str, char **env)
{
	int check;

	check = check_escape_dollar(*str, lst.i);
	if ((*str)[lst.i] == '$' && (*str)[lst.i + 1] == '?')
		lst.i += 2;
	else if (((*str)[lst.i] == '$' && (*str)[lst.i + 1] != '?') || check == 1)
		lst = change_dollar_helper(lst, str, env);
	check = check_escape_dollar(*str, lst.i);
	if ((*str)[lst.i] != '$' && (*str)[lst.i] != '\'' && (*str)[lst.i] != '\0' && check == 0)
		lst.i += 1;
	lst.on = 0;
	return (lst);
}

char    *take_away_dollar(char *s)
{
    int i;
    int len;
    char *string;

    len = ft_strlen(s);
    string = (char *) ft_calloc(sizeof (char), len + 1);
    if (!string)
        return (NULL);
    if (s[0] == '\\')
    {
        i = 0;
        while (s[i] == '\\')
            i += 1;
        if (s[i] == '$')
            i += 1;
    }
    else
        i = 1;
    len = 0;
    while (s[i] != '\0')
        string[len++] = s[i++];
    string[len] = '\0';
    return (string);
}
