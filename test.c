#include <stdio.h>
#include <stdlib.h>
#include "Libft/libft.h"
#include "minishell.h"



int main()
{
  char *ar[] = {"ls", NULL};
  int pid;
  int fd = open("test", O_CREAT | O_APPEND | O_RDWR , 0644);
  dup2(fd, 1);
  printf("test\n");
  return 0;
}