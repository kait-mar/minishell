#include "../minishell.h"

int	condition1(char **bult, int k)
{
	return (bult[g_global.j_echo][k] == '\\'
			&& (bult[g_global.j_echo][k + 1] == '$'
			|| bult[g_global.j_echo][k + 1] == '"'
			|| bult[g_global.j_echo][k + 1] == '\''
			|| bult[g_global.j_echo][k + 1] == '\\'));
}

int	condition2(char **bult, int k)
{
	return (bult[g_global.j_echo][k] == '\\'
			&& (bult[g_global.j_echo][k + 1] == '$'
			|| bult[g_global.j_echo][k + 1] == '"'
			|| bult[g_global.j_echo][k + 1] == '\''));
}

int 	to_quote(char *s, int i)
{
	if (s[i] == '\\')
	{
		while (s[i] == '\\')
			i += 1;
		if (s[i] == '"' || s[i] == '\'')
			return (1);
	}
	return (0);
}

int 	count_es_quote(char *s)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\\' && to_quote(s, i) == 1)
		{
			j = 0;
			while (s[i] == '\\')
				increment_counters(&j, &i);
			if ((j % 2) == 0)
				count += (j / 2 );
			else
				count += (j / 2) + 1;
			if (s[i] == '"' || s[i] == '\'')
				count += 1;
		}
		else
			count += 1;
		i += 1;
	}
	return (count);
}

char	*es_quote(char *s)
{
	int		i;
	int		j;
	char	*str;

	str = malloc(sizeof(char ) * count_es_quote(s) + 1);
	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\\' && to_quote(s, i) == 1)
		{
			while (s[i] == '\\')
			{
				i += 1;
				str[j++] = s[i];
				if (s[i] == '\\')
					i += 1;
			}
		}
		else
			str[j++] = s[i];
		i += 1;
	}
	str[j] = '\0';
	return (str);
}
