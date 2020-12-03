#include <errno.h>
#include <unistd.h>
#include <stdio.h>


int	main()
{

	write(1, "labhairi", 8);
	print("--> %d\n", errno);
	return(0);
}
