//from the real-time-embedded-systems course

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <sched.h>
#include <syslog.h>
#include <sys/utsname.h>
#include <string.h>

#define NUM_THREADS 12

typedef struct
{
    int threadIdx;
} threadParams_t;


// POSIX thread declarations and scheduling attributes
//
pthread_t threads[NUM_THREADS];
threadParams_t threadParams[NUM_THREADS];


void *counterThread(void *threadp)
{
    int sum=0, i;
    threadParams_t *threadParams = (threadParams_t *)threadp;

    syslog(LOG_INFO, "[COURSE:1][ASSIGNMENT:1] Hello World from Thread!");

    for(i=1; i < (threadParams->threadIdx)+1; i++)
        sum=sum+i;
 
    printf("Thread idx=%d, sum[0...%d]=%d\n", 
           threadParams->threadIdx,
           threadParams->threadIdx, sum);
}


int main (int argc, char *argv[])
{
   int i;

   //open the syslogs
   openlog("logs", LOG_PID, LOG_USER);
	
   //retrieve the system's name
   struct utsname systemName;
   memset(&systemName, 0x00, sizeof(systemName));
   if( -1 != uname(&systemName))
   {
      printf(" uname: %s\n", systemName.sysname);
      syslog(LOG_INFO, "[COURSE:1][ASSIGNMENT:1]:%s", systemName.sysname);   
   }

   syslog(LOG_INFO, "[COURSE:1][ASSIGNMENT:1] Hello World from Main!");
   for(i=0; i < NUM_THREADS; i++)
   {
       threadParams[i].threadIdx=i;

       pthread_create(&threads[i],   // pointer to thread descriptor
                      (void *)0,     // use default attributes
                      counterThread, // thread function entry point
                      (void *)&(threadParams[i]) // parameters to pass in
                     );

   }

   //pthreads joint is needed, becuse otherwise the main pogram will not wait for 
   //the threads and it could just end.
   for(i=0;i<NUM_THREADS;i++)
       pthread_join(threads[i], NULL);

   //report completion
   printf("TEST COMPLETE\n");

   //close syslog
   closelog();
}


/** basic Makefile

INCLUDE_DIRS = 
LIB_DIRS = 
CC=gcc

CDEFS=
CFLAGS= -Wall -O0 -g $(INCLUDE_DIRS) $(CDEFS)
LIBS= 

HFILES= 
CFILES= pthread.c

SRCS= ${HFILES} ${CFILES}
OBJS= ${CFILES:.c=.o}

all:	pthread

clean:
	-rm -f *.o *.d
	-rm -f pthread

pthread: pthread.o
	$(CC) $(LDFLAGS) $(CFLAGS) -o $@ $@.o -lpthread

depend:

.c.o:
	$(CC) $(CFLAGS) -c $<
  
**/
