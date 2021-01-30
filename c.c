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
/*	char *buf = calloc(1, 1024);

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
    fprintf(stderr, "exiting\n");*/
    int fd[2];
    char *buf = calloc(1, 1024);
    pipe(fd);
    if (dup2(fd[1], 1) == -1)
    {
        fprintf(stderr, "Error in dup2 \n");
        exit(EXIT_FAILURE);
    }
    fprintf(stdout, "Testin in the same process\n");
    close(fd[1]);
    if (dup2(fd[0], 0) == -1)
    {
        fprintf(stderr, "Error in dup2 \n");
        exit(EXIT_FAILURE);
    }
    read(fd[0], buf, 20);
    close(fd[0]);
    fprintf(stderr, "buf ==> %s\n", buf);
    exit(EXIT_SUCCESS);
}