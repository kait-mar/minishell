
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <term.h>
#include <curses.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>


int     int_put(int c)
{
    write(1, &c, 1);
    return (0);
}

typedef struct s_append
{
    char *string;
    struct s_append *next;
}               t_append;

void    push_end(t_append **head, char *string)
{
    t_append *last;
    t_append *push_end;

    last = *head;
    if (!(push_end = (t_append *) malloc(sizeof (t_append))))
        return ;
    push_end->string = strdup(string);
    if (*head == NULL)
    {
        *head = push_end;
        push_end->next = NULL;
        return ;
    }
    while (last->next != NULL)
        last = last->next;
    last->next = push_end;
    push_end->next = NULL;
}

int  main()
{
    t_append *push;
    int fd;
    pid_t pid;
    int stat;

    push = NULL;
    push_end(&push, "labhairi");
    push_end(&push, "mouaad");
    push_end(&push, "casa");
    push_end(&push, "negra");
    fd = open(".minishell_history", O_CREAT | O_APPEND | O_RDWR, S_IRWXU);
    if ((pid = fork()) > 0)
    {
        if (dup2(fd, 1) == -1)
            printf("%s\n", strerror(errno));
        while (push != NULL)
        {
            printf("%s\n", push->string);
            push = push->next;
        }
        exit(EXIT_SUCCESS);
    }
    else
        exit(EXIT_FAILURE);
    waitpid(pid, &stat, WUNTRACED);
    printf("Done\n");
    return (0);
}
