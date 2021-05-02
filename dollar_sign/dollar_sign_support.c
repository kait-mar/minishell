#include "../minishell.h"

int     count_escap(char *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i] == '\\')
	{
		count += 1;
		i += 1;
	}
	return (count);
}

char    *adding_escape(char *s, int count)
{
	int		i;
	int		j;
	int		len;
	char	*str;

	i = 0;
	j = 0;
	len = ft_strlen(s) + count + 1;
	if (!(str = (char *) ft_calloc(sizeof (char ), len)))
		return (NULL);
	while (count > 0)
	{
		str[i] = '\\';
		i += 1;
		count -= 1;
	}
	while (s[j] != '\0')
	{
		str[i] = s[j];
		i += 1;
		j += 1;
	}
	str[i] = '\0';
	return (str);
}

int     dollar_len(char *str, int i)
{
	int	count;
	int	j;
	int	k;

	j = 0;
	count = 0;
	while (str[i] == '\\')
	{
		i += 1;
		count += 1;
	}
	if (str[i] == '$')
	{
		i += 1;
		count += 1;
	}
	while (str[i] != '\0' && str[i] != '$' && str[i] != ' '
			&& str[i] != '>' &&  str[i] != '<' &&  str[i] != ';' && str[i] != '\t'
			&& str[i] != '\'' && str[i] != '"' && str[i] != '|' && str[i] != ','
			&& str[i] != '[' && str[i] != ']')
	{
		count += 1;
		i += 1;
	}
	return (count);
}

char    *take_word(char *str, int i, int len)
{
	char	*s;
	int		j;
	int		count;

	j = 0;
	count = 0;
	if (!(s = (char *) ft_calloc(sizeof (char), len + 1)))
		return (NULL);
	while (i < len)
	{
		s[j] = str[i];
		i += 1;
		j += 1;
	}
	s[j] = '\0';
	if (count > 0)
		s = adding_escape(s, count);
	return (s);
}

int    dollar_parsing(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\'')
			return (0);
		else if (s[i] == '\"' && s[i + 1] != '$')
			return (0);
		else if (s[i] == '$' && active(s, i) == 0)
			return (0);
		else if (s[i] == '$' && (s[i + 1] == ' ' || s[i + 1] == '\0' || s[i + 1] == '\\'))
			return (0);
		i += 1;
	}
	return (1);
}