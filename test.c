#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "Libft/libft.h"
//#include "minishell.h"

typedef struct s_pipe
{
    pid_t pid;
    int     x;
    struct s_pipe *next;
}               t_pipe;


int main()
{
    //struct  stat stats;
/*
    t_pipe *nmbr;
    t_pipe *head;
    t_pipe  *tmp;
    int x = 0;

    head = (t_pipe *) malloc(sizeof (t_pipe));
    head->x = x;
    head->pid = fork();
    head->next = NULL;
    tmp = head;
    for (int i = 0; i < 2; i++)
    {
        x += 1;
        nmbr->x = x;
        nmbr->pid = fork();
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = nmbr;
        tmp->next->next =NULL;
        nmbr = (t_pipe *) malloc(sizeof (t_pipe));
    }
    nmbr->next = NULL;
    while (head != NULL)
    {
        printf("pid  ==> %d\n", head->pid);
        printf("x ==> %d\n", head->x);
        head = head->next;
    }
   printf("End of process\n");*/
    /*if (stat("/Users/molabhai/Desktop/minishell/a.out", &stats) == -1)
        ft_printf("error ==> %s\n", strerror(errno));*/
    char *argv[] = {"ls", "-l", NULL};
    execve("/bin/ls", argv, NULL);
    return (0);
}