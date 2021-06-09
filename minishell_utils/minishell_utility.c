#include "../minishell.h"

int	check_escape_space(char *string, int i)
{
	while (string[i] != '\0')
	{
		if (string[i] == '\\')
		{
			while (string[i] == '\\')
				i++;
			if (string[i] == ' ')
				return (1);
		}
		i += 1;
	}
	return (0);
}

void	remove_space_support(char *string, int *i, int *start, int *end)
{
	if (ft_strcmp(string, "") == 0)
	{
		*start = *i;
		*end = 0;
		return ;
	}
	while (string[*i] == ' ')
		*i += 1;
	*start = *i;
	*end = ft_strlen(string) - 1;
	while (string[*end] == ' ')
		(*end)--;
	if (string[*end] == '\\')
		*end += 1;
}

char	*remove_space_quotes(char *str, char *string, int *j, int *start)
{
	if (string[*start] == '"')
	{
		str[(*j)++] = string[(*start)++];
		while (string[(*start)] != '\0' && string[(*start)] != '"')
		{
			str[(*j)] = string[*start];
			*j += 1;
			*start += 1;
		}
		if (string[*start] == '"')
			str[(*j)++] = string[(*start)++];
	}
	else if (string[*start] == '\'')
	{
		str[(*j)++] = string[(*start)++];
		while (string[*start] != '\0' && string[*start] != '\'')
		{
			str[(*j)] = string[*start];
			*j += 1;
			*start += 1;
		}
		if (string[*start] == '\'')
			str[(*j)++] = string[(*start)++];
	}
	return (str);
}

char	*remove_space_core(char *str, char *string, int *j, int *start)
{
	if (string[*start] == '"' || string[*start] == '\'')
		str = remove_space_quotes(str, string, j, start);
	else if (string[*start] == ' ' && active(string, *start) == 1)
	{
		str[(*j)++] = string[(*start)++];
		while (string[*start] == ' ')
			(*start)++;
	}
	else if (string[*start] == ' ' && active(string, *start) == 0)
		str[(*j)++] = string[(*start)++];
	else
		str[(*j)++] = string[(*start)++];
	return (str);
}

char	*remove_space(char *string)
{
	int		i;
	int		j;
	int		start;
	int		end;
	char	*str;

	j = 0;
	i = 0;
	str = (char *) malloc(sizeof (char ) * (count_new(string) + 1));
	if (!str)
		return (NULL);
	remove_space_support(string, &i, &start, &end);
	while (string[start] != '\0' && start <= end)
		str = remove_space_core(str, string, &j, &start);
	str[j] = '\0';
	return (str);
}
