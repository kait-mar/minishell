#include "../minishell.h"

char    *last_print_env_case(char *bult, char **env, int which_quote, int *status)
{
    char    *s;

    s = NULL;
    if (*bult == '$' && *(bult + 1) == '?')
    {
        ft_printf("%d", *status);
        s = bult + 2;
    }
    else
        s = print_env2(bult, env, which_quote, status);
    return (s);
}

int     check_echo_flag(char **bult, int *i)
{
    char    **str;
    int     b;

    b = 0;
    str = ft_split(*bult, ' ');
    if (*str == NULL)
        return (0);
    while (*str)
    {
        if (flag_strcmp(*str, "-n") == 0)
        {
            str++;
            *i = 1;
            *bult = skip_first_word(&(*bult));
        }
        else
        {
            b = 1;
            break;
        }
    }
    if (b == 1)
        return (0);
    else if (**bult == '\0')
        bult++;
    return (1);
}

void    echo_complet(char **bult, char **env, int *status, int i)
{
    put_cases(bult, env, status);
	if (i == 0)
        my_putchar('\n');
	*status = 0;
}