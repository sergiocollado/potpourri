#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <sched.h>
#include <syslog.h>
#include <sys/utsname.h>
#include <string.h>

#define NUM_THREADS (128)  //definition of the number of threads

typedef struct
{
    int threadIdx;
    int count;
} threadParams_t;
//definition of a structure to pass as a parameter to the treads
//  - thradIdx: thread identifier
//  - count: number to add to.


// POSIX thread declarations and scheduling attributes
//
pthread_t threads[NUM_THREADS];
threadParams_t threadParams[NUM_THREADS];


// Unsafe global
int gsum=0;
struct utsname systemName;  //to get the uname of the system

void *incThread(void *threadp)
{

    int i;
    threadParams_t *threadParams = (threadParams_t *)threadp;
    int value = 0;

    for(i=0; i<threadParams->count; i++)
    {
        value+=i;
    }
    syslog(LOG_INFO, "[COURSE:1][ASSIGNMENT:2]: Thread idx: %d sum[1..%d]=%d\n", threadParams->threadIdx, threadParams->count, value);
    printf("thread idx=%d, sum[0..%d]=%d\n", threadParams->threadIdx, threadParams->count, value);
}

int main (int argc, char *argv[])
{
   int rc;
   int i=0;

   //open the syslogs
   openlog("logs", LOG_PID, LOG_USER);

   struct utsname systemName;
   memset(&systemName, 0x00, sizeof(systemName));
   if( -1 != uname(&systemName))
   {
      printf(" uname: %s\n", systemName.sysname);
      syslog(LOG_INFO, "[COURSE:1][ASSIGNMENT:2]:%s", systemName.sysname);   
   }

   for(i=0; i<NUM_THREADS; ++i)
   {
       threadParams[i].threadIdx=i; //define thread id
       threadParams[i].count=i;     //define number to add to.
	   
       pthread_create(&threads[i],   // pointer to thread descriptor
                     (void *)0,      // use default attributes
                     incThread,      // thread function entry point
                     (void *)&(threadParams[i]) // parameters to pass in
                     );
   }

   for(i=0; i<NUM_THREADS; ++i)
     pthread_join(threads[i], NULL);
   //wait for all the threads to be finished,
   //otherwise the main() function could pass through and end 
   // without the completion of the threads.

   //close syslog
   closelog();
   
   printf("TEST COMPLETE\n");
}
