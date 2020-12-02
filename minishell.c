#include "minishell.h"

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

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

int main(int argc, char **argv, char **env)
{
    char    *line;
    char    **bult;
    int     i;

    i = 0;
    get_next_line(0, &line);
   //line = "echo hello world";
    bult = ft_split(line, ' ');
    if (ft_strcmp(bult[0], "echo") == 0)
    {
        bult++;
        if (ft_strcmp(*bult, "-n") == 0)
        {
            bult++;
            i = 1;
        }
        while (*(bult + 1) != NULL)
        {
            ft_putstr(*bult);
            write(1, " ", 1);
            bult++;
        }
        ft_putstr(*bult);
        if (i == 0)
            ft_putchar('\n');
    }
    return (0);
}
