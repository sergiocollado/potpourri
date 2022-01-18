// from: https://stackoverflow.com/questions/3056307/how-do-i-use-mqueue-in-a-c-program-on-a-linux-based-system
// ref: https://users.cs.cf.ac.uk/Dave.Marshall/C/node25.html#SECTION002500000000000000000
/*
mq_open() -- Connects to, and optionally creates, a named message queue.

mq_close() -- Ends the connection to an open message queue.

mq_unlink() -- Ends the connection to an open message queue and causes the queue to be removed when the last process closes it.

mq_send() -- Places a message in the queue.

mq_receive() -- Receives (removes) the oldest, highest priority message from the queue.

mq_notify() -- Notifies a process or thread that a message is available in the queue.

mq_setattr() -- Set or get message queue attributes.
*/

// ref: https://man7.org/linux/man-pages/man3/mq_open.3.html
// reference: https://www.opensourceforu.com/2021/05/the-usefulness-of-posix-message-queues/

//compile: gcc -o server server.c -lrt

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <mqueue.h>

#include "common.h"

int main(int argc, char **argv)
{
    mqd_t mq;
    struct mq_attr attr;
    char buffer[MAX_SIZE + 1];
    int must_stop = 0;

    /* initialize the queue attributes */
    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = MAX_SIZE;
    attr.mq_curmsgs = 0;

    /* create the message queue */
    mq = mq_open(QUEUE_NAME, O_CREAT | O_RDONLY, 0644, &attr);
    CHECK((mqd_t)-1 != mq);

    do {
        ssize_t bytes_read;

        /* receive the message */
        bytes_read = mq_receive(mq, buffer, MAX_SIZE, NULL);
        CHECK(bytes_read >= 0);

        buffer[bytes_read] = '\0';
        if (! strncmp(buffer, MSG_STOP, strlen(MSG_STOP)))
        {
            must_stop = 1;
        }
        else
        {
            printf("Received: %s\n", buffer);
        }
    } while (!must_stop);

    /* cleanup */
    CHECK((mqd_t)-1 != mq_close(mq));
    CHECK((mqd_t)-1 != mq_unlink(QUEUE_NAME));

    return 0;
}
