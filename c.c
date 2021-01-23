#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
char    *ft_strchr(char *s, char c)
{
    while (*s)
    {
        if (*s == c)
            return (s);
        s++;
    }
    return (NULL);
}

int		main(int ac, char **av, char **envp)
{
	char *buf = calloc(1, 1024);

	buf[0] = '\n';
	buf[1] = '\0';
	while (ft_strchr(buf, '\n'))
	{
        memset(buf, 0, 1024);
        fprintf(stderr, "reading from stdin\n");
        read(0, buf, 1023);
        fprintf(stderr, "writing to stdout\n");
        write(1, buf, 1023);
    }
    fprintf(stderr, "exiting\n");
}
