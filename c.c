
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <term.h>
#include <curses.h>
#include <unistd.h>
#include <fcntl.h>


int     int_put(int c)
{
    write(1, &c, 1);
    return (0);
}

int  main()
{
	char *termtype;
	int success;
	static char	buffer[2048];
	char *str;
	char *up_arr;
	char *down_arr;
	char *tty_name;
	char *key_s;
	char *buffer_adress;
	int r;
	struct termios tp;
	int fd;

	termtype = getenv("TERM");
	success =  tgetent(buffer, termtype);
	if (success != 1)
	    printf("Eroor in tgetent\n");
    if (!(str = (char *) calloc(1, 10)))
        return (-1);
    if (!(buffer_adress = (char *) malloc(strlen(buffer))))
        return (-1);
    tty_name = ttyname(STDIN_FILENO);
    up_arr = tgetstr("ku", &buffer_adress);
    down_arr = tgetstr("kd", &buffer_adress);
    fd = open(tty_name, O_RDWR | O_NOCTTY);
    if (tcgetattr(fd, &tp) == -1)
        exit(-1);
    tp.c_lflag &= ~(ECHO | ICANON) ;
    if (tcsetattr(fd, TCSANOW, &tp) == 1)
        exit (-1);
    r = read(fd, str, 10);
    tp.c_lflag |= (ECHO | ICANON);
    if (tcsetattr(fd, TCSANOW, &tp) == 1)
        exit (-1);
    int i = 0;
    while (str[i])
        printf("str [i] == > %d\n", str[i++]);
    int j = 0;
    while (down_arr[j])
        printf("down_arr [j] == > %d\n", down_arr[j++]);
    if (memcmp(str, up_arr, 3) == 0)
        printf("Arrow Up\n");
    else if (memcmp(str, down_arr, 3) == 0)
        printf("Arrow Down\n");
    printf("isatty ==> %d\n", isatty(STDIN_FILENO));
    printf("tty name ==> %s\n", ttyname(STDIN_FILENO));
    printf("up_arr ==> %s\n", up_arr);
    printf("down_arr ==> %s\n", down_arr);
    return (0);
}
