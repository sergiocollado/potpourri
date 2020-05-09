#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

/* for compiling it: gcc -pthread pthreadsprog01.c */
/* to run it: ./a.out */
/* to stop it: Ctrl+C */

void* myturn(void* arg)
{
    for(int i=0; i < 10; ++i)
    {
        printf("ping ...\t\t%d\n", i);  
        sleep(1);
    }
    return NULL;
}

void* yourturn(void)
{
    for(int i=0; i < 7; ++i)
    {
        printf("\t... pong\t %d\n", i);
        sleep(1);
    }
    return NULL;
}

int main(void) 
{
    pthread_t mynewpthread;
    pthread_create(&mynewpthread, NULL, myturn, NULL);
    /* the functions used for threads must follow some rules,
      like returning (void *) */

    yourturn();

    pthread_join(mynewpthread, NULL);
    /* pthread_join will wait up to the given thread is finished
        and then the program will continue */

}

/** 

 the output should look like:
 
 	... pong	 0
ping ...		0
	... pong	 1
ping ...		1
	... pong	 2
ping ...		2
	... pong	 3
ping ...		3
	... pong	 4
ping ...		4
	... pong	 5
ping ...		5
	... pong	 6
ping ...		6
ping ...		7
ping ...		8
ping ...		9

**/
