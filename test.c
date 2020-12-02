#include <stdio.h>
int main( int argc, char *argv[], char *envp[])
{
int i;
/* echo all environment args */
for (i = 0 ; envp[i] ; i++)
printf( "envp[%d]: %s\n", i, envp[i] );
}
