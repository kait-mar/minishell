#include "../minishell.h"

void	ft_putstr(char *s)
{
	if (s == NULL)
		return ;
	while (*s != '\0')
	{
		write(1, &(*s), 1);
		s++;
	}
}

int	only_star(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '*' && s[i] != '\0')
		i++;
	if ((s[i] == '*' && (s[i + 1] == ' '
				|| s[i + 1] == '\0' || s[i + 1] == '\t'))
		|| (s[i] == '*' && (s[i - 1] == ' '
				|| s[i - 1] == '\0' || s[i - 1] == '\t')))
		return (1);
	else
		return (0);
}

int	print_esp(char **bult, int k)
{
	my_putchar(bult[g_global.j_echo][k]);
	k++;
	return (k);
}

int	print(char **bult, int *status)
{
	int		i;
	int		k;
	char	*str;

	i = 0;
	k = 0;
	str = bult[g_global.j_echo];
	bult[g_global.j_echo] = es_quote(bult[g_global.j_echo]);
	free(str);
	str = bult[g_global.j_echo];
	bult[g_global.j_echo] = escape_normal(bult[g_global.j_echo]);
	free(str);
	while (bult[g_global.j_echo][k] != '\0')
	{
		if (bult[g_global.j_echo][k] == '$'
			&& bult[g_global.j_echo][k + 1] == '?')
		{
			ft_putnbr_fd(*status, 1);
			k += 2;
		}
		else
			k = print_esp(bult, k);
		i = 1;
	}
	return (i);
}

char	*skip_first_word(char *str)
{
	char	*s;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while ((str[i] == ' ' || str[i] == '\t') && str[i] != '\0')
	{
		i++;
	}
	if (str[i] != '\0')
	{
		while (str[i] != ' ' && str[i] != '\t' && str[i] != '\0')
			i++;
		if (str[i] == ' ')
			i++;
		s = malloc(ft_strlen(str) - i + 1);
		while (str[i] != '\0')
			s[j++] = str[i++];
		s[j] = '\0';
		return (s);
	}
	return (str);
}
