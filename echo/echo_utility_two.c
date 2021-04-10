#include "../minishell.h"

int		find_how_many(char *s, char c)
{
	int	i;

	i = 0;
	while (*s)
	{
		if (*s == c && (i == 0 || *(s - 1) != '\\'))
			i++;
		s++;
	}
	return (i);
}

int		first_word_lenght(char *s)
{
	int	i;

	i = 0;
	if (s == NULL)
		return (-1);
	while (s[i] && (s[i] == ' ' || s[i] == '\t'))
		i++;
	while (s[i])
	{
		if (skip_quote(s, &i))
			continue ;
		else if (ft_isalnum(s[i]))
			i++;
		else
			break ;
	}
	return (i);
}

int		fill_first_word(char *s, char **string, int *i, int *j)
{
	int	on;

	on = 0;
	if (s[*i] == '\'')
	{
		(*string)[(*j)++] = s[(*i)++];
		while (s[*i] && s[*i] != '\'')
			(*string)[(*j)++] = s[(*i)++];
		if (s[*i] == '\'')
			(*string)[(*j)++] = s[(*i)++];
		on = 1;
	}
	else if (s[*i] == '"')
	{
		(*string)[(*j)++] = s[(*i)++];
		while (s[*i] && s[*i] != '"')
			(*string)[(*j)++] = s[(*i)++];
		if (s[*i] == '"')
			(*string)[(*j)++] = s[(*i)++];
		on = 1;
	}
	return (on);
}

char	*take_first_word(char *s)
{
	char	*string;
	int		i;
	int		j;

	j = 0;
	if (s == NULL)
        return (NULL);
	if (!(string = malloc(first_word_lenght(s) + 1)))
		return (0);
	i = 0;
	while (s[i])
	{
		if (fill_first_word(s, &string, &i, &j))
			continue ;
		else if (ft_isalnum(s[i]))
			string[j++] = s[i++];
		else
			break ;
	}
	string[j] = '\0';
	return (string);
}

void	stream_directory()
{
	DIR				*dir;
	struct dirent	*pdir;

	if ((dir = opendir(".")) != NULL)
	{
		while ((pdir = readdir(dir)) != NULL)
		{
			if (*pdir->d_name != '.')
			{
				ft_putstr(pdir->d_name);
				write(1, " ", 1);
			}
		}
		closedir(dir);
	}
}
