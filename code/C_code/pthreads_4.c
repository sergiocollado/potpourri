#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <sched.h>

#define COUNT  1000

typedef struct     
{
    //this defined structi will be used as a parameter for the threads creation
    // so we can identify each thread with an Id number.
    int threadIdx;
} threadParams_t;


// POSIX thread declarations and scheduling attributes
//
pthread_t threads[2];
threadParams_t threadParams[2];


// Unsafe global
int gsum=0;

void *incThread(void *threadp)
{
    //this function will be assinged to the incremental threads.
    int i;

    threadParams_t *threadParams = (threadParams_t *)threadp;
    //the passed parameter void* threadp is converted to the threadParams struct, 
    // so it's Id can be retrieved later.

    for(i=0; i<COUNT; i++)
    {
        gsum=gsum+i;
        printf("Increment thread idx=%d, gsum=%d\n", threadParams->threadIdx, gsum);
        //the sum is done here, in a loop from 0 to COUNT, adding to the global variable 'gsum'
        //in the trace we can record the Id of the thread that did it.
    }
}


void *decThread(void *threadp)
{
    //this function will be assinged to the decremental threads.
    int i;

    threadParams_t *threadParams = (threadParams_t *)threadp;
    //the passed parameter void* threadp is converted to the threadParams struct, 
    // so it's Id can be retrieved later.

    for(i=0; i<COUNT; i++)
    {
        gsum=gsum-i;
        printf("Decrement thread idx=%d, gsum=%d\n", threadParams->threadIdx, gsum);
        //the sum is done here, in a loop from 0 to COUNT, decrementing to the global variable 'gsum'
        //in the trace we can record the Id of the thread that did it.
    }
}


int main (int argc, char *argv[])  //definition of the main program.
{
   int rc;        //this variable rc is not used. 
   int i=0;       //definition of counter variable and initialization to zero. i=0.

   threadParams[i].threadIdx=i; //i=0;
   //the first thread [0], we define its threadIdx as 0.

   pthread_create(&threads[i],   // pointer to thread descriptor
                  (void *)0,     // use default attributes
                  incThread, // thread function entry point
                  (void *)&(threadParams[i]) // parameters to pass in
                 );
   //function to create the thread, in the function entry point we can see the incThread(), is called.

   i++;  //+1 is added to the counter variable. i=1.

   threadParams[i].threadIdx=i;
   //the parameters for the second thread[1] are defined, so its threadIdx=1

   pthread_create(&threads[i], (void *)0, decThread, (void *)&(threadParams[i]));
   //the second thread (thread[1]) is created, and from the function entry point 
   // we can see it is a decremental thread.

   for(i=0; i<2; i++)
     pthread_join(threads[i], NULL);
   //at the end of the main() function we have to wait for completion of all the threads
   //otherwise the main() function will end and terminate even the threads that are still running.


   printf("TEST COMPLETE\n");  //report completion.
}
