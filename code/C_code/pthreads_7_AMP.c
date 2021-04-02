#define _GNU_SOURCE   //needed for CPU macros
#include <pthread.h>  //needed to use posix threads
#include <stdio.h>    //standard input/outpu
#include <stdlib.h>   //standard library
#include <errno.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sched.h>    //needed to use SCHED_FIFO real-time scheduling policy
#include <syslog.h>   //needed to use system log. /var/log/sys
#include <string.h>   //needed to use string function
#include <unistd.h>   //to use getpid

#define NUM_THREADS 128
#define SCHED_POLICY SCHED_FIFO

typedef struct
{
    int threadIdx;
} threadParams_t;


// POSIX thread declarations and scheduling attributes
pthread_t threads[NUM_THREADS];
pthread_t mainthread;
pthread_t startthread;
threadParams_t threadParams[NUM_THREADS];

pthread_attr_t fifo_sched_attr;
pthread_attr_t orig_sched_attr;
struct sched_param fifo_param;

// get_uname() function executes the uname -a command and returns the command in the parameter
void get_uname(char *uname_str) 
{
    FILE *pf; //file object
    char command[20];
    char data[512];

    //create uname command
    sprintf(command, "uname -a"); 

    //create pipe to read and execute uname command
    pf = popen(command,"r"); 

    //get ouput of unmame command, store in data
    fgets(data, 512 , pf);
    
    //Format uname -a output
    strcpy(uname_str, "System uname -a: ");
    strcat(uname_str, data);

    if (pclose(pf) != 0)
    {
        fprintf(stderr," Error: Failed to close command stream \n");
    }

    return;
}

void print_scheduler(void)
{
    int schedType = sched_getscheduler(getpid());

    switch(schedType)
    {
        case SCHED_FIFO:
            printf("Pthread policy is SCHED_FIFO\n");
            break;
        case SCHED_OTHER:
            printf("Pthread policy is SCHED_OTHER\n");
            break;
        case SCHED_RR:
            printf("Pthread policy is SCHED_RR\n");
            break;
        default:
            printf("Pthread policy is UNKNOWN\n");
    }
}


void set_scheduler(void)
{
    int max_prio = 0, rc = 0, cpuidx = 0;
    cpu_set_t cpuset;

    printf("INITIAL "); print_scheduler();

    pthread_attr_init(&fifo_sched_attr);
    pthread_attr_setinheritsched(&fifo_sched_attr, PTHREAD_EXPLICIT_SCHED);
    pthread_attr_setschedpolicy(&fifo_sched_attr, SCHED_POLICY);
    CPU_ZERO(&cpuset);
    cpuidx=(1); //AMP - bound to a single core
    CPU_SET(cpuidx, &cpuset);
    pthread_attr_setaffinity_np(&fifo_sched_attr, sizeof(cpu_set_t), &cpuset);

    max_prio=sched_get_priority_max(SCHED_POLICY);
    fifo_param.sched_priority=max_prio;    

    if((rc=sched_setscheduler(getpid(), SCHED_POLICY, &fifo_param)) < 0)
    {
       perror("sched_setscheduler");
       perror("pthread_getaffinity_np");
       perror("******** WARNING: sched_setscheduler");
       printf("******** WARNING: sched_setscheduler\n");
       print_scheduler();
       abort(); //terminate the program - Aborted (core dumped)
    }

    pthread_attr_setschedparam(&fifo_sched_attr, &fifo_param);

    printf("ADJUSTED "); print_scheduler();
}


void *counterThread(void *threadp)
{
    int sum=0;
    threadParams_t *threadParams = (threadParams_t *)threadp;
    double start=0.0, stop=0.0;
    struct timeval startTime, stopTime;

    //get start time
    gettimeofday(&startTime, 0);
    start = ((startTime.tv_sec * 1000000.0) + startTime.tv_usec)/1000000.0;

    //compute
    for(int i=0; i < (threadParams->threadIdx + 1); ++i)
    {
        sum=sum+i;
    }

    //get end time
    gettimeofday(&stopTime, 0);
    stop = ((stopTime.tv_sec * 1000000.0) + stopTime.tv_usec)/1000000.0;

    //report
    printf("\nThread idx=%d, sum[0...%d]=%d, running on CPU=%d, start=%lf, stop=%lf", 
           threadParams->threadIdx,
           threadParams->threadIdx, sum, sched_getcpu(),
           start, stop);
    syslog(LOG_INFO, "Thread idx: %d sum[1..%d]=%d Running on core: %d",
             threadParams->threadIdx, threadParams->threadIdx, sum, sched_getcpu());

    return (void*)NULL;
 }


void *starterThread(void *threadp)
{
   printf("starter thread running on CPU=%d\n", sched_getcpu());

   for(int i=0; i < NUM_THREADS; ++i)
   {
       threadParams[i].threadIdx=i;

       pthread_create(&threads[i],               // pointer to thread descriptor
                      &fifo_sched_attr,          // use FIFO RT max priority attributes
                      counterThread,             // thread function entry point
                      (void *)&(threadParams[i]) // parameters to pass in
                     );

   }

   for(int i=0; i<NUM_THREADS; ++i)   //wait for termination of all the workers
   {
       pthread_join(threads[i], NULL);
   }

   return (void*)NULL;
}


int main (int argc, char *argv[])
{
   //get the name of the system
   char uname_str[512];
   get_uname(uname_str);
   printf("%s\n", uname_str);

   cpu_set_t cpuset;
   set_scheduler();

   CPU_ZERO(&cpuset);

   // get affinity set for main thread
   mainthread = pthread_self();

   // Check the affinity mask assigned to the thread 
   int rc = pthread_getaffinity_np(mainthread, sizeof(cpu_set_t), &cpuset);
   if (rc != 0)
   {
       perror("pthread_getaffinity_np");
       perror("******** WARNING: sched_setscheduler");
       printf("******** WARNING: sched_setscheduler\n");
       print_scheduler();
       return EXIT_FAILURE;
   }
   else
   {
       printf("main thread running on CPU=%d, CPUs =", sched_getcpu());

       for (int j = 0; j < CPU_SETSIZE; j++)
           if (CPU_ISSET(j, &cpuset))
               printf(" %d", j);

       printf("\n");
   }


   // reset logs
   system("sudo sh -c 'cat /dev/null > /var/log/syslog'");

   //open the syslogs
   openlog("logs_ASM", LOG_PID | LOG_CONS | LOG_NDELAY , LOG_USER);

   //report the name of the system
   syslog(LOG_INFO, "%s", uname_str);

   //launch master thread
   pthread_create(&startthread,       // pointer to thread descriptor
                  &fifo_sched_attr,   // use FIFO RT max priority attributes
                  starterThread,      // thread function entry point
                  (void *)0           // parameters to pass in
                 );

   pthread_join(startthread, NULL);

   printf("\nTEST COMPLETE\n");

   //close syslog
   closelog();

   return EXIT_SUCCESS;
}

/*********** makefile ***************

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
****************************/
