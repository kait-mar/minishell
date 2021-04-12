#include "../minishell.h"

void    last_put_cases(char **bult, char **env, int *status, int *i)
{
    int which_quote;

    which_quote = 0;
    if (**bult == 39 || **bult == 34)
        *bult = which_trim(*bult, &which_quote);
    if ((find_without(*bult, '$') == 0 && find_without(*bult, '"') == 0
        && find_without(*bult, '\'') == 0) || which_quote == 39)
    {
        if (find_without(*bult, '\\') == 0 || which_quote == 39)
        {
            if (*i == 1)
                write(1, " ", 1);
            ft_putstr(*bult);
            *i = 0;
        }
        else
            bult = put_cases1(bult);
    }
    else
    {
        if (print_env(*bult, env, 0, status) == 1)
            write(1, " ", 1);
    }
}

char    *which_trim(char *bult, int *which_quote)
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
    return (s);
}

char	*in_between_cases(char *bult, char **env, int *status)
{
	char	*s;

	s = NULL;
	if (*bult == '\'')
	{
			s = ft_strtrim(bult, "'");
			ft_putstr(bult);
	}
	else
	{
		s = ft_strtrim(bult, "\"");
		print_env(bult, env, 1, status);
	}
	return (s);
}

int		print_env_condition(char *bult)
{
	return (*bult != '$' && *bult != '\0' && (*bult != '\\' || *(bult + 1) != '\\') &&
               (*bult != '\\' || *(bult + 1) != '$') && (*bult != '\\' || *(bult + 1) != '\'') &&
               (*bult != '\\' || *(bult + 1) != '"'));
}

int		which_quote_condition(char *bult, int which_quote)
{
	return ((*bult == '$' && ((which_quote == 0 && (*(bult + 1) == '\0' || *(bult + 1) == ' '))
        || (which_quote == 1 && (*(bult + 1) == 39 || *(bult + 1) == 34 || *(bult + 1) == '\0'
        || *(bult + 1) == ' ')))));
}