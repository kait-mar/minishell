#include <stdio.h>
#include <stdlib.h>
#include "Libft/libft.h"
#include "minishell.h"



int main()
{
  char *ar[] = {"ls", NULL};
  int pid;
  int fd = open("test.txt", O_WRONLY | O_CREAT);
  dup2(fd, 1);
  printf("try this redirection meta\n");
  return 0;
}