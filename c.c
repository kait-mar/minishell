#include <stdio.h>
#include <string.h>
#include <errno.h>

int	main()
{
	printf("errno ==> %s\n", strerror(errno));
}
