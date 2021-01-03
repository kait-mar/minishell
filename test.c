#include <stdio.h>
#include <stdlib.h>
#include "Libft/libft.h"
#include "minishell.h"



int main()
{
  char *ar[] = {"ls", NULL};
  int pid;
  int fd = open("test.txt", O_WRONLY | O_CREAT);
  int pipe_fd[2];
  char *s = "labhairi mouocaad";
  char *str;

  str = (char *) calloc(sizeof (char ) , (strlen(s) + 1));
  if (str == NULL)
      return (1);
  pipe(pipe_fd);
  if ((pid = fork()) < 0)
  {
      printf("%s\n", strerror(errno));
      return (1);
  }
  else if (pid == 0)
  {
      close (pipe_fd[1]);
      read(pipe_fd[0], str, strlen(s));
      printf("str == > %s\n", str);
      exit(0);
  }
  else
  {
      close(pipe_fd[0]);
      write(pipe_fd[1], s, strlen(s));
      wait(NULL);
      printf("Here\n");
      close(pipe_fd[1]);
  }
  free(str);
  return 0;
}