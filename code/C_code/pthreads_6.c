#define _GNU_SOURCE       //needed for macros as CPU_ZERO, CPU_SET
#include <pthread.h>      //to use posix thrads
#include <stdlib.h>       //to use the standard library
#include <stdio.h>        //to use input/output
#include <syslog.h>       //to use the system log
#include <sys/utsname.h>  //to use uname()
#include <string.h>       //to use strings
#include <sys/sysinfo.h>  //to get the number of processors
#include <errno.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sched.h>        //to use scheduling policies
#include <unistd.h>       //to use getpid

#define NUM_THREADS (128)
#define SCHED_POLICY SCHED_FIFO
#define MAX_ITERATIONS (1)

typedef struct
{
    int threadIdx;
    int count;
} threadParams_t;


// POSIX thread declarations and scheduling attributes
pthread_t threads[NUM_THREADS];
threadParams_t threadParams[NUM_THREADS];
pthread_t mainthread;
pthread_attr_t main_attr;
pthread_t startthread;
pthread_attr_t fifo_sched_attr;
pthread_attr_t orig_sched_attr;
struct sched_param fifo_param;
struct sched_param main_param;
pid_t mainpid;

// Unsafe global
int gsum=0;

void* counterThread(void *threadp)
{
    threadParams_t *threadParams = (threadParams_t *)threadp;
    int value = 0;
    double start = 0.0, stop = 0.0;
    struct timeval startTime, stopTime;

    gettimeofday(&startTime, 0);
    start = ((startTime.tv_sec * 1000000.0) + startTime.tv_usec)/1000000.0;

    for(int iterations=0; iterations < MAX_ITERATIONS; iterations++)
    {
        for(int i=1; i < (threadParams->threadIdx)+1; i++)
            value+=i;
    }

    gettimeofday(&stopTime, 0);
    stop = ((stopTime.tv_sec * 1000000.0) + stopTime.tv_usec)/1000000.0;

    syslog(LOG_INFO, "[COURSE:1][ASSIGNMENT:3]: Thread idx: %d sum[1..%d]=%d Running on core: %d\n", threadParams->threadIdx, threadParams->count, value, sched_getcpu());

    printf("thread idx=%d, sum[0..%d]=%d Running on core:%d, start: %lf, stop: %lf\n", threadParams->threadIdx, threadParams->count, value, sched_getcpu(), start, stop);
    return NULL;
}

void print_scheduler(void)
{
   int schedType, scope;

   schedType = sched_getscheduler(getpid());

   switch(schedType)
   {
     case SCHED_FIFO:
           printf("Pthread Policy is SCHED_FIFO\n");
           break;
     case SCHED_OTHER:
           printf("Pthread Policy is SCHED_OTHER\n");
       break;
     case SCHED_RR:
           printf("Pthread Policy is SCHED_OTHER\n");
           break;
     default:
       printf("Pthread Policy is UNKNOWN\n");
   }

   pthread_attr_getscope(&main_attr, &scope);

   if(scope == PTHREAD_SCOPE_SYSTEM)
     printf("PTHREAD SCOPE SYSTEM\n");
   else if (scope == PTHREAD_SCOPE_PROCESS)
     printf("PTHREAD SCOPE PROCESS\n");
   else
     printf("PTHREAD SCOPE UNKNOWN\n");
}

void set_scheduler(void)
{
    int max_prio, rc, cpuidx;
    cpu_set_t cpuset;

    printf("INITIAL "); print_scheduler(); printf("\n");

    pthread_attr_init(&fifo_sched_attr);
    pthread_attr_setinheritsched(&fifo_sched_attr, PTHREAD_EXPLICIT_SCHED);
    pthread_attr_setschedpolicy(&fifo_sched_attr, SCHED_POLICY);
    CPU_ZERO(&cpuset);
    cpuidx=(3);
    CPU_SET(cpuidx, &cpuset);
    pthread_attr_setaffinity_np(&fifo_sched_attr, sizeof(cpu_set_t), &cpuset);

    max_prio = sched_get_priority_max(SCHED_POLICY);
    fifo_param.sched_priority=max_prio;    

    if((rc=sched_setscheduler(getpid(), SCHED_POLICY, &fifo_param)) < 0)
    {
        perror("sched_setscheduler");
        printf("sched_setscheduler error!\n");
    }

    pthread_attr_setschedparam(&fifo_sched_attr, &fifo_param);

    printf("ADJUSTED "); print_scheduler();  printf("\n"); fflush(stdout);
}

void* starterThread(void *threadp)
{
    printf("Starter thread running in cpu: %d\n", sched_getcpu());

    //launch the threads
    for(int i = 0; i < NUM_THREADS; ++i)
    {
       threadParams[i].threadIdx=i;
       threadParams[i].count=i;
       pthread_create(&threads[i],     // pointer to thread descriptor
                     &fifo_sched_attr, // use attributes
                     counterThread,        // thread function entry point
                     (void *)&(threadParams[i]) // parameters to pass in
                     );     

    }

   //wait for al the threads
   for(int i=0; i<NUM_THREADS; ++i)
     pthread_join(threads[i], NULL);

   return NULL;
}

// get_uname() function executes the uname -a command and prints the output 
// to the syslog in the format required by the hw
void get_uname() 
{
	FILE *pf; //file object
	char command[20]; 
	char data[512];
	char str[512];

    //create uname command
    sprintf(command, "uname -a"); 

    //create pipe to read and execute uname command
    pf = popen(command,"r"); 

    //get ouput of unmame command, store in data
    fgets(data, 512 , pf);
    
    //Format uname -a output
    strcpy(str, "[COURSE:1][ASSIGNMENT:2]");
	strcat(str, data);
	
	//write to syslog with priority LOG_INFO
	syslog(LOG_INFO, str);
	//atempt to close pipe, print error message if failed
    if (pclose(pf) != 0)
        fprintf(stderr," Error: Failed to close command stream \n");

    return;
}

int main (int argc, char *argv[])
{
   cpu_set_t cpuset;

   //open the syslogs
   openlog("syslogs_prog.3", LOG_PID | LOG_CONS | LOG_NDELAY ,LOG_USER);

   //retrieve the system's name
   struct utsname systemName;
   memset(&systemName, 0x00, sizeof(systemName));
   if( -1 != uname(&systemName))
   {
      printf(" uname: %s\n", systemName.sysname);
      syslog(LOG_INFO, "[COURSE:1][ASSIGNMENT:3]:%s", systemName.sysname);   
   }

   printf("This system has %d processors with %d available\n", get_nprocs_conf(), get_nprocs());

   // get affinity set for main thread
   mainthread = pthread_self();

   // Check the affinity mask assigned to the thread 
   int rc = pthread_getaffinity_np(mainthread, sizeof(cpu_set_t), &cpuset);
   if (rc != 0)
   {
       perror("pthread_getaffinity_np");
       printf("pthread_getaffinity_np!\n");                
   }                      
   else
   {
       printf("main thread running on CPU=%d, CPUs =", sched_getcpu());

       for (int j = 0; j < CPU_SETSIZE; j++)
           if (CPU_ISSET(j, &cpuset))
               printf(" %d", j);

       printf("\n");
   }

  mainpid=getpid();

  int rt_max_prio = sched_get_priority_max(SCHED_POLICY); // The maximum priority value is determined 

  rc=sched_getparam(mainpid, &main_param);
  main_param.sched_priority=rt_max_prio;

   if ((rc=sched_setscheduler(getpid(), SCHED_POLICY, &main_param)) < 0)
   {
    perror("******** WARNING: sched_setscheduler");
    printf("******** WARNING: sched_setscheduler\n");
    print_scheduler();
    return EXIT_FAILURE;
   }

   print_scheduler();
   //system("sudo sh -c 'cat /dev/null > /var/log/syslog'"); // Truncate the syslog file
   //system("sudo sh -c ': > /var/log/syslog'"); // Clean syslog file
   //system("logger -t \"[COURSE:1][ASSIGNMENT:3]\" `uname -a`"); // Send output of uname-a to syslog file

   pthread_create(&startthread,      // pointer to thread descriptor
                  &fifo_sched_attr,  // use FIFO RT max priority attributes
                  starterThread,     // thread function entry point
                  (void *)0 // parameters to pass in
                 );

   pthread_join(startthread, NULL);


   //close syslog
   closelog();
   printf("TEST COMPLETE\n");
   return EXIT_SUCCESS;
}

/** makefile
INCLUDE_DIRS = 
LIB_DIRS = 
CC=gcc

CDEFS=
CFLAGS= -Wall -O3 $(INCLUDE_DIRS) $(CDEFS)
LIBS= 

HFILES= 
CFILES= pthread.c

SRCS= ${HFILES} ${CFILES}
OBJS= ${CFILES:.c=.o}

all:	pthread

clean:
	-rm -f *.o *.d
	-rm -f perfmon pthread

distclean:
	-rm -f *.o *.d
	-rm -f pthread

pthread: pthread.o
	$(CC) $(LDFLAGS) $(CFLAGS) -o $@ $@.o -lpthread

depend:

.c.o:
	$(CC) $(CFLAGS) -c $<
  
end makefile **/
