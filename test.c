#include <stdio.h>
#include <stdlib.h>
#include "Libft/libft.h"
#include "minishell.h"



int main()
{
    int    fd[2];
    int     pid;
    char    buff[20];
    pid = fork();
    pipe(fd);
    if (pid == 0)
    {
        close(fd[0]);
        write(fd[1], "hello from child", 20);
        close(fd[1]);
        exit(EXIT_SUCCESS);
    }
    else
    {
        close(fd[1]);
        wait(NULL);
        read(fd[0], buff, 20);
        close(fd[0]);
    }
    printf("the incoming string is : |%s|\n", buff);
    return 0;
}