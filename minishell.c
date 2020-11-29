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

int main(int argc, char **argv)
{
    char    *line;
    char    **bult;

    get_next_line(0, &line);
    bult = ft_split(line, ' ');
    //start your code from here
    // exp : if (ft_strcmp(bult[0], "echo") == 0) ===> do and do .. etc
    
    return (0);
}
