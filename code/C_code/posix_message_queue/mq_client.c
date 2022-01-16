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

//compile: gcc -o client mq_client.c -lrt

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <mqueue.h>

#include "common.h"


int main(int argc, char **argv)
{
    mqd_t mq;
    char buffer[MAX_SIZE];

    /* open the mail queue */
    mq = mq_open(QUEUE_NAME, O_WRONLY);
    CHECK((mqd_t)-1 != mq);


    printf("Send to server (enter \"exit\" to stop it):\n");

    do {
        printf("> ");
        fflush(stdout);

        memset(buffer, 0, MAX_SIZE);
        fgets(buffer, MAX_SIZE, stdin);

        /* send the message */
        CHECK(0 <= mq_send(mq, buffer, MAX_SIZE, 0));

    } while (strncmp(buffer, MSG_STOP, strlen(MSG_STOP)));

    /* cleanup */
    CHECK((mqd_t)-1 != mq_close(mq));

    return 0;
}
