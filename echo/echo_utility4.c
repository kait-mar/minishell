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

int		only_star(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '*' && s[i] != '\0')
		i++;
	if ((s[i] == '*' && (s[i + 1] == ' ' || s[i + 1] == '\0' || s[i + 1] == '\t')) ||
		(s[i] == '*' && (s[i - 1] == ' ' || s[i - 1] == '\0' || s[i - 1] == '\t')))
		return (1);
	else
		return (0);
}

int		 print(char **bult, char **env, int *status)
{
	int		j;
	int		i;
	int		fd;
	int		k;

	i = 0;
	k = 0;
	if (only_star(bult[g_global.j_echo]) == 1)
		stream_directory();
	while (bult[g_global.j_echo][k] != '\0')
    {
		if (bult[g_global.j_echo][k] == '$' && bult[g_global.j_echo][k + 1] == '?')
		{
			ft_printf("%d", *status);
			k += 2;
			//bult[g_global.j_echo] = bult[g_global.j_echo] + 2;
		}
		else
		{
			my_putchar(bult[g_global.j_echo][k]);
      		//(*bult)++;
			  k++;
		}
	    i = 1;
    }
	return (i);
}

char	*skip_first_word(char **str)
{
	char	*s;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (((*str)[i] == ' ' || (*str)[i] == '\t') && (*str)[i] != '\0')
	{
		i++;
	}
	if ((*str)[i] != '\0')
	{
		while ((*str)[i] != ' ' && (*str)[i] != '\t' && (*str)[i] != '\0')
			i++;
		if ((*str)[i] == ' ')
		    i++;
		s = malloc(ft_strlen(*str) - i + 1);
		while ((*str)[i] != '\0')
			s[j++] = (*str)[i++];
		s[j] = '\0';
		/*this free causes a problem !!
		if (*str)
			free(*str);*/
		return (s);
	}
	return (*str);
}
