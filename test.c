#include "minishell.h"


int main()
{
  char *s = "'-n ' hello 'world'    here 'we go   !'yes";
  //int i = coun(s, 39);
  //printf("%d\n", i);
  char **line = take_only_carac( "'-n ' hello 'world'    here 'we go   !'yee");
  int i =0;
  while (line[i] )
  {
    printf("|%s|\n", line[i]);
	i += 1;
  }
  return 0;
}
