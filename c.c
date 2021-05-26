
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
int	find(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c && (i == 0 || (i - 1 >= 0 && str[i - 1] != '\\')))
			return (1);
		i++;
	}
	return (0);
}
int  main()
{
    printf("the returbed value is %d\n", find("\\\\\\\\", 39));
}

