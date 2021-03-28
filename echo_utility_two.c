#include "minishell.h"

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

char	*take_first_word(char *s)
{
	char	*string;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (s == NULL)
        return NULL;
	while (s[i] && (s[i] == ' ' || s[i] == '\t'))
		i++;
	while (s[i])
	{
		if (s[i] == '\'')
		{
			i++;
			while (s[i] && s[i] != '\'')
				i++;
			if (s[i] == '\'')
				i++;
		}
		else if (s[i] == '"')
		{
			i++;
			while (s[i] && s[i] != '"')
				i++;
			if (s[i] == '"')
				i++;
		}
		else if (ft_isalnum(s[i]))
			i++;
		else
			break;
	}
	//this has been replaced by bellow
	/*while ((ft_isalnum(s[i]) || s[i] == '\'' || s[i] == '"') && s[i])
		i++;*/
	if (!(string = malloc(i + 1)))
		return (0);
	i = 0;
	/*while (s[i] && (s[i] == ' ' || s[i] == '\t'))
		i++;*/
	while ((ft_isalnum(s[i]) || s[i] == '\'' || s[i] == '"' || s[i] == '\\') && s[i])
		string[j++] = s[i++];
	while (s[i] && (s[i] == ' ' || s[i] == '\t'))
		i++;
	while (s[i])
	{
		if (s[i] == '\'')
		{
			string[j++] = s[i++];
			while (s[i] && s[i] != '\'')
				string[j++] = s[i++];
			if (s[i] == '\'')
				string[j++] = s[i++];
		}
		else if (s[i] == '"')
		{
			string[j++] = s[i++];
			while (s[i] && s[i] != '"')
				string[j++] = s[i++];
			if (s[i] == '"')
				string[j++] = s[i++];
		}
		else if (ft_isalnum(s[i]))
			string[j++] = s[i++];
		else
			break;
	}

	/*while ((ft_isalnum(s[i]) || s[i] == '\'' || s[i] == '"') && s[i])
		string[j++] = s[i++];*/
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
	while (*bult != '\0' && *bult != '\\')
		bult++;
	while (*bult != '\0' && *bult == '\\')
	{
		bult++;
		i++;
	}
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
int		find_without(char *bult, char c)
{
	int	i;

	i = 0;
	while (bult[i] != '\0')
	{
		if (bult[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*trim_once(char *s)
{
	char	*str;
	int		i;
	int		j;

	if (s == NULL)
		return (NULL);
	str = malloc(ft_strlen(s) - 1);
	i = 1;
	j = 0;
	while (s[i + 1] != '\0')
	{
		str[j++] = s[i++];
	}
	str[j] = '\0';
	return (str);
}