#include "minishell.h"


int main()
{
  char *s = "'-n ' hello 'world'    here 'we go   !'yes";
  //int i = coun(s, 39);
  //printf("%d\n", i);
  printf("HerEQQEQ\n");
  char **line = take_only_carac(s);
  int i =0;
  while (line[i] != NULL)
  {
    printf("|%s|\n", line[i]);
	i += 1;
  }
  return 0;
}
