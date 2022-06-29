// references: https://man7.org/linux/man-pages/man2/select_tut.2.html
// references: https://man7.org/linux/man-pages/man2/select.2.html

#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>

int main(void)
{
    fd_set rfds;
    struct timeval tv;
    int retval;

    /* Watch stdin (fd 0) to see when it has input. */

    FD_ZERO(&rfds);
    FD_SET(0, &rfds);  // also can be used: STDIN_FILENO: https://man7.org/linux/man-pages/man3/stdout.3.html

    /* Wait up to five seconds. */

    tv.tv_sec = 5;
    tv.tv_usec = 0;

    retval = select(1, &rfds, NULL, NULL, &tv);
    /* Don't rely on the value of tv now! */

    if (retval == -1)
        perror("select()");
    else if (retval)
        printf("Data is available now.\n");
        /* FD_ISSET(0, &rfds) will be true. */
        /* Since select() modifies its file descriptor sets, if the call
           is being used in a loop, then the sets must be reinitialized
           before each call.
        */
     else
        printf("No data within five seconds.\n");

    exit(EXIT_SUCCESS);
}
