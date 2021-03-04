#include "minishell.h"

int		find_how_many(char *s, char c)
{
	int	i;

	i = 0;
	while (*s)
	{
		if (*s == c)
			i++;
		s++;
	}
	return (i);
}

char	*take_first_word(char *s)
{
	char	*string;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (s == NULL)
        return NULL;
	while ((ft_isalnum(s[i]) || s[i] == '\'' || s[i] == '"') && s[i])
		i++;
	if (!(string = malloc(i + 1)))
		return (0);
	i = 0;
	while (s[i] && (s[i] == ' ' || s[i] == '\t'))
		i++;
	while ((ft_isalnum(s[i]) || s[i] == '\'' || s[i] == '"') && s[i])
		string[j++] = s[i++];
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

int		how_many_escape(char *bult)
{
	int	i;

	i = 0;
//	printf("the bult is %s\n", bult);
	while (bult[i] != '\0' && bult[i] == '\\')
		i++;
//	ft_printf("it returned %d\n", i);
	return (i);
}

int		find_dollar_esacpe(char *bult, char c)
{
	int	i;

	i = 0;
	while (bult[i] != '\0')
	{
		if (bult[i + 1] != '\0' && bult[i] == '\\' && bult[i + 1] == '$')
			return (1);
		i++;
	}
	return (0);
}