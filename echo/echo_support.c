#include "../minishell.h"

void	last_put_cases(char **bult, char **env, int *status, int *i)
{
	int	which_quote;

	which_quote = 0;
	if (bult[g_global.j_echo][0] == 34)
		g_global.e_quote = 1;
	if (bult[g_global.j_echo][0] == 39 || bult[g_global.j_echo][0] == 34)
		bult[g_global.j_echo] = which_trim(bult[g_global.j_echo], &which_quote);
	if (last_put_condition(bult, which_quote))
	{
		if (which_quote == 39 || find_without(bult[g_global.j_echo], '\\') == 0 )
		{
			if (*i == 1)
				write(1, " ", 1);
			ft_putstr(bult[g_global.j_echo]);
			*i = 0;
		}
		else
			bult = put_cases1(bult);
	}
	else
	{
		if (print_env(bult[g_global.j_echo], env, 0, status) == 1)
			write(1, " ", 1);
	}
}

char	*which_trim(char *bult, int *which_quote)
{
	char	*s;

	s = NULL;
	if (*bult == 39)
	{
		s = trim_once(bult);
		*which_quote = 39;
	}
	else
	{
		s = trim_once(bult);
		*which_quote = 34;
	}
	free(bult);
	return (s);
}

char	*in_between_cases(char *bult, char **env, int *status)
{
	char	*s;

	s = bult;
	if (*bult == '\'')
	{
		s = ft_strtrim(s, "'");
		ft_putstr(s);
	}
	else
	{
		s = ft_strtrim(s, "\"");
		print_env(s, env, 1, status);
	}
	free(bult);
	return (s);
}

int	print_env_condition(char *bult)
{
	return (*bult != '$' && *bult != '\0' && (*bult != '\\' || *(bult + 1) != '\\')
		&& (*bult != '\\' || *(bult + 1) != '$')
		&& (*bult != '\\' || *(bult + 1) != '\'')
		&& (*bult != '\\' || *(bult + 1) != '"'));
}

int	which_quote_condition(char *bult, int which_quote)
{
	return ((*bult == '$' && ((which_quote == 0
					&& (*(bult + 1) == '\0' || *(bult + 1) == ' '))
				|| (which_quote == 1 && (*(bult + 1) == 39
						|| *(bult + 1) == 34 || *(bult + 1) == '\0'
						|| *(bult + 1) == ' ')))));
}
