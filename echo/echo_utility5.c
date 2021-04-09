#include "../minishell.h"

void			my_putchar(char c)
{
    write(1, &c, 1);
}

void	put_normal(char **split, char **env, int i, int *status)
{
	while (*(split + 1) != NULL)
	{
		if (print(split, env, status) == 1)
			write(1, " ", 1);
		split++;
	}
	print(split, env, status);
	if (i == 1)
		my_putchar(' ');
}

char    *print_env1(char *bult)
{
    int     j;

    j = how_many_escape(bult);
    if (j % 2 != 0)
    {
        while (*(bult + 1) == '\\')
        (bult)++;
    }
    else
    {
        while (*bult == '\\')
            (bult)++;
    }
    j /= 2;
    while (--j >= 0)
        ft_putchar('\\');
    return(bult);
}

char    *check_print(char *bult)
{
    bult++;
    while (ft_isalnum(*bult) == 1 && *bult)
        bult++;
    while (*bult)
    {
        my_putchar(*bult);
        bult++;
    }
    return (bult);
}

char    *print_env2(char *bult, char **env, int which_quote, int *status)
{
    char    **str;
    int     i;
    char    **tabs;
    int     j;

    i = 0;
    if (which_quote == 0)
        str = ft_split(bult, ' ');
    else if (which_quote == 1)
    {
        if (*(str = ft_split(bult, ' ')) != NULL)
        {
            if (*(str = ft_split(str[0], '\'')) != NULL)
                str = ft_split(str[0], '"');
        }
    }
    if (*str != NULL)
        i = print_envir(str, env, tabs);
    if (*bult == '$' && *(bult + 1) != '\0')
        bult = check_print(bult);
    return (bult);
}

int    print_envir(char **str, char **env, char **tabs)
{
    int j;
    int i;

    j = 0;
    i = 0;
    while (env[j])
    {
        tabs = ft_split(env[j], '=');
        if (ft_strcmp(tabs[0], take_first_word(str[0] + 1)) == 0)
        {
            ft_putstr(tabs[1]);
            i = 1;
            break ;
        }
        j++;
    }
    return (i);
}
