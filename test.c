#include <stdio.h>
#include <stdlib.h>
#include "Libft/libft.h"
#include "minishell.h"



int main()
{
  char *ar[] = {"ls", NULL};
  int pid;
  int fd = open("test.txt", O_RDWR | O_CREAT, S_IRWXU);
  write(fd, "hello", 5);
  close(fd);
  int fd2 = open("test.txt", O_RDWR | O_CREAT, S_IRWXU);
  write(fd, "hi", 2);
  close(fd2);
  return 0;
}