// Sam Siewert, December 2017
//
// modified by Sergio 
//
// Sequencer Generic
//
// The purpose of this code is to provide an example for how to best
// sequence a set of periodic services for problems 
//

/* For this example: - Non-Harmonic, RM Failure, EDF and LLF Success


| TASK  | PERIOD |  FREQ  | MULT. FREQ |  WCET | UTILITY |
|  S1   |    3   |   0.33 |    3       |   1   |   33.3% |
|  S2   |    6   |   0.16 |    1.5     |   2   |   33.3% |
|  S3   |    9   |   0.11 |    1       |   3   |   33.3% |


LUB = 77.98
LCM = 18       // period for repetition
U_tot = 100%


RM schedule:

0ms    10ms   20ms   30ms   40     50     60    70      80     90     100    110    120    130    140    150    160    170    180   [ms]
|--S1--|--S2--|--S2--|--S1--|--S3--|--S3--|--S1--|--S2--|--S2--|--S1--|--MISSED-S3--|--S1--|--S2--|--S2--|--S1--|--S1--|--S3--|--S3--|
                                                              ^^^ Here S3 misses the deadline, doesn't manage to do 3 computation slices in the 9 slices period!!
<--------T1----------><--------T1---------><--------T1---------><--------T1---------><--------T1---------><--------T1---------><--------T1--------->
<--------------------T2-------------------><--------------------T2------------------><--------------------T2------------------> ...          
<------------------------------T3------------------------------><------------------------------T3------------------------------> ...

          
EDF schedule:

    0ms    10ms   20ms   30ms   40     50     60    70      80     90     100    110    120    130    140    150    160    170    180   [ms]
    |--S1--|--S2--|--S2--|--S1--|--S3--|--S3--|--S1--|--S3--|--S2--|--S1--|--S2--|--S3--|--S1--|--S2--|--S2--|--S1--|--S3--|--S3--| ...

    <--------T1----------><--------T1---------><--------T1---------><--------T1---------><--------T1---------><--------T1---------><--------T1--------->
    <--------------------T2-------------------><--------------------T2------------------><--------------------T2------------------> ...          
    <------------------------------T3------------------------------><------------------------------T3------------------------------> ...

Urgency table (TTD: TIME TO DEADLINE)

 S1:    3      X      X      3     X      X       3      X      X       3     X      X      3       X     X      3     X      X
 S2:    6      5      4      X     X      X       6      5      4       3     2      X      6       5     4      X     X      X
 S3:    9      8      7      6     5      4       3      2      X       9     8      7      6       5     4      3     2      x


LFF schedule: 
 
    0ms    10ms   20ms   30ms   40     50     60    70      80     90     100    110    120    130    140    150    160    170    180   [ms]
    |--S1--|--S2--|--S2--|--S1--|--S3--|--S3--|--S1--|--S3--|--S2--|--S1--|--S2--|--S3--|--S1--|--S2--|--S3--|--S1--|--S2--|--S3--| ...

    <--------T1----------><--------T1---------><--------T1---------><--------T1---------><--------T1---------><--------T1---------><--------T1--------->
    <--------------------T2-------------------><--------------------T2------------------><--------------------T2------------------> ...          
    <------------------------------T3------------------------------><------------------------------T3------------------------------> ...

Laxity table (TTD-TR)

 S1:   2      X      X      2      X      X      2      X      X      2      X      X       2      X      X     2      X      X    
 S2:   4      3      3      X      X      X      4      3      2      2      1      X       4      3      3     2      1      X    
 S3:   6      5      4      3      2      2      2      1      X      6      5      4       4      3      2     2      1      0    

*/

// This is necessary for CPU affinity macros in Linux
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <pthread.h>
#include <sched.h>
#include <time.h>
#include <semaphore.h>

#include <syslog.h>
#include <sys/time.h>
#include <sys/sysinfo.h>
#include <sys/utsname.h>
#include <string.h>
#include <errno.h>

#define USEC_PER_MSEC (1000)
#define NANOSEC_PER_SEC (1000000000)
#define NUM_CPU_CORES (1)
#define TRUE (1)
#define FALSE (0)

#define PERIODS (11)
#define NUM_THREADS (3+1)  // 3 services + sequencer
#define TASK_DURATION 9.75  // time duration for the tasks

// Of the available user space clocks, CLOCK_MONONTONIC_RAW is typically most precise and not subject to 
// updates from external timer adjustments
//
// However, some POSIX functions like clock_nanosleep can only use adjusted CLOCK_MONOTONIC or CLOCK_REALTIME
//
//#define MY_CLOCK_TYPE CLOCK_REALTIME
//#define MY_CLOCK_TYPE CLOCK_MONOTONIC
#define MY_CLOCK_TYPE CLOCK_MONOTONIC_RAW
//#define MY_CLOCK_TYPE CLOCK_REALTIME_COARSE
//#define MY_CLOCK_TYPE CLOCK_MONTONIC_COARSE

int abortTest=FALSE;
int abortS1=FALSE, abortS2=FALSE, abortS3=FALSE;
sem_t semS1, semS2, semS3;
struct timespec start_time_val;
volatile double start_realtime;
int first_iteration = TRUE;

typedef struct
{
    int threadIdx;
    unsigned long long sequencePeriods;
} threadParams_t;

void *Sequencer(void *threadp);

void *Service_1(void *threadp);
void *Service_2(void *threadp);
void *Service_3(void *threadp);

// function prototypes
double getTimeMsec(void);
double realtime(struct timespec *tsptr);
void print_scheduler(void);
void fibonacciForXms(float timeMs);

int main(void)
{
    int rc, scope;
    cpu_set_t threadcpu;
    pthread_t threads[NUM_THREADS];
    threadParams_t threadParams[NUM_THREADS];
    pthread_attr_t rt_sched_attr[NUM_THREADS];

    int rt_max_prio, rt_min_prio;
    struct sched_param rt_param[NUM_THREADS];
    struct sched_param main_param;
    pthread_attr_t main_attr;
    pid_t mainpid;
    cpu_set_t allcpuset;

    printf("Starting Sequencer Demo\n");

    clock_gettime(MY_CLOCK_TYPE, &start_time_val); start_realtime=realtime(&start_time_val);

    printf("System has %d processors configured and %d available.\n", get_nprocs_conf(), get_nprocs());

    CPU_ZERO(&allcpuset);

    for(int i=0; i < NUM_CPU_CORES; i++)
        CPU_SET(i, &allcpuset);

    printf("Using CPUS=%d from total available.\n", CPU_COUNT(&allcpuset));

    // initialize the sequencer semaphores
    //
    if (sem_init (&semS1, 0, 0)) { printf ("Failed to initialize S1 semaphore\n"); exit (EXIT_FAILURE); }
    if (sem_init (&semS2, 0, 0)) { printf ("Failed to initialize S2 semaphore\n"); exit (EXIT_FAILURE); }
    if (sem_init (&semS3, 0, 0)) { printf ("Failed to initialize S3 semaphore\n"); exit (EXIT_FAILURE); }

    mainpid=getpid(); //get pid of current process

    rt_max_prio = sched_get_priority_max(SCHED_FIFO);
    rt_min_prio = sched_get_priority_min(SCHED_FIFO);

    rc=sched_getparam(mainpid, &main_param);
    main_param.sched_priority=rt_max_prio;    //set current process with max prio
    rc=sched_setscheduler(getpid(), SCHED_FIFO, &main_param);
    if (rc < 0) { perror("main_param"); exit(EXIT_FAILURE); }
    print_scheduler();

    pthread_attr_getscope(&main_attr, &scope);

    if (scope == PTHREAD_SCOPE_SYSTEM)
      printf("PTHREAD SCOPE SYSTEM\n");
    else if (scope == PTHREAD_SCOPE_PROCESS)
      printf("PTHREAD SCOPE PROCESS\n");
    else
      printf("PTHREAD SCOPE UNKNOWN\n");

    printf("rt_max_prio=%d\n", rt_max_prio);
    printf("rt_min_prio=%d\n", rt_min_prio);

    for (int i=0; i < NUM_THREADS; i++)
    {

      CPU_ZERO(&threadcpu);
      CPU_SET(1, &threadcpu);  //set to CPU_1

      rc=pthread_attr_init(&rt_sched_attr[i]);
      rc=pthread_attr_setinheritsched(&rt_sched_attr[i], PTHREAD_EXPLICIT_SCHED);
      rc=pthread_attr_setschedpolicy(&rt_sched_attr[i], SCHED_FIFO);
      rc=pthread_attr_setaffinity_np(&rt_sched_attr[i], sizeof(cpu_set_t), &threadcpu);

      rt_param[i].sched_priority=rt_max_prio-i;
      pthread_attr_setschedparam(&rt_sched_attr[i], &rt_param[i]);

      threadParams[i].threadIdx=i;
    }
   
    printf("Service threads will run on %d CPU cores\n", CPU_COUNT(&threadcpu));

    // Create Service threads which will block awaiting release for:
    //

    // Service_1 = RT_MAX-1	@ 50 Hz
    //
    rt_param[1].sched_priority=rt_max_prio-1;
    pthread_attr_setschedparam(&rt_sched_attr[1], &rt_param[1]);
    rc=pthread_create(&threads[1],               // pointer to thread descriptor
                      &rt_sched_attr[1],         // use specific attributes
                      //(void *)0,               // default attributes
                      Service_1,                 // thread function entry point
                      (void *)&(threadParams[1]) // parameters to pass in
                     );
    if (rc < 0)
        perror("pthread_create for service 1");
    else
        printf("pthread_create successful for service 1\n");

    // Service_2 = RT_MAX-2	@ 20 Hz
    //
    rt_param[2].sched_priority=rt_max_prio-2;
    pthread_attr_setschedparam(&rt_sched_attr[2], &rt_param[2]);
    rc=pthread_create(&threads[2], &rt_sched_attr[2], Service_2, (void *)&(threadParams[2]));
    if (rc < 0)
        perror("pthread_create for service 2");
    else
        printf("pthread_create successful for service 2\n");

    // Service_3 = RT_MAX-3	@ 10 Hz
    //
    rt_param[3].sched_priority=rt_max_prio-3;
    pthread_attr_setschedparam(&rt_sched_attr[3], &rt_param[3]);
    rc=pthread_create(&threads[3], &rt_sched_attr[3], Service_3, (void *)&(threadParams[3]));
    if (rc < 0)
        perror("pthread_create for service 3");
    else
        printf("pthread_create successful for service 3\n");

    // Wait for service threads to initialize and await relese by sequencer.
    //
    // Note that the sleep is not necessary of RT service threads are created wtih 
    // correct POSIX SCHED_FIFO priorities compared to non-RT priority of this main
    // program.
    //
    usleep(5000);
 
    // reset logs
    system("sudo sh -c 'cat /dev/null > /var/log/syslog'");

    //open the syslogs and writhe the system name (uname -a)
    openlog("sequencer", LOG_PID | LOG_CONS | LOG_NDELAY , LOG_USER);
    struct utsname systemName;
    memset(&systemName, 0x00, sizeof(systemName));
    if( -1 != uname(&systemName))
    {
       printf(" uname: %s\n", systemName.sysname);
       syslog(LOG_INFO, "[COURSE:2][ASSIGNMENT:7]: %s %s %s %s %s", systemName.sysname, systemName.nodename, systemName.release, systemName.version, systemName.machine);   
    }

    // Create Sequencer thread, which like a cyclic executive, is highest prio
    printf("Start sequencer\n");
    threadParams[0].sequencePeriods=PERIODS;

    // Sequencer = RT_MAX	@ 100 Hz
    //
    rt_param[0].sched_priority=rt_max_prio;
    pthread_attr_setschedparam(&rt_sched_attr[0], &rt_param[0]);
    rc=pthread_create(&threads[0], &rt_sched_attr[0], Sequencer, (void *)&(threadParams[0]));
    if (rc < 0)
        perror("pthread_create for sequencer service 0");
    else
        printf("pthread_create successful for sequencer service 0\n");

    for (int i=0;i<NUM_THREADS;i++)
        pthread_join(threads[i], NULL);

    printf("\nTEST COMPLETE\n");
    exit(EXIT_SUCCESS);
}

void *Sequencer(void *threadp)
{
    struct timeval current_time_val;
    struct timespec delay_time = {0,10000000}; // delay for 10  msec, 100 Hz
    struct timespec remaining_time;
    //double current_time;
    double residual;
    int rc, delay_cnt=0;
    unsigned long long seqCnt=0;
    threadParams_t *threadParams = (threadParams_t *)threadp;

    gettimeofday(&current_time_val, (struct timezone *)0);
    //syslog(LOG_CRIT, "Sequencer thread @ sec=%d, msec=%d\n", (int)(current_time_val.tv_sec-start_time_val.tv_sec), (int)current_time_val.tv_usec/USEC_PER_MSEC);
    printf("Sequencer thread @ sec=%d, msec=%d\n", (int)(current_time_val.tv_sec-start_time_val.tv_sec), (int)current_time_val.tv_usec/USEC_PER_MSEC);

    clock_gettime(MY_CLOCK_TYPE, &start_time_val); start_realtime=realtime(&start_time_val);  //time initialization

    do
    {
        delay_cnt=0; residual=0.0;

        do
        {
            rc=nanosleep(&delay_time, &remaining_time);

            if(rc == EINTR)
            { 
                residual = remaining_time.tv_sec + ((double)remaining_time.tv_nsec / (double)NANOSEC_PER_SEC);

                if(residual > 0.0) printf("residual=%lf, sec=%d, nsec=%d\n", residual, (int)remaining_time.tv_sec, (int)remaining_time.tv_nsec);
 
                delay_cnt++;
            }
            else if(rc < 0)
            {
                perror("Sequencer nanosleep");
                exit(-1);
            }
           
        } while((residual > 0.0) && (delay_cnt < 100));
       
        if (delay_cnt > 1) printf("Sequencer looping delay %d\n", delay_cnt);

        if (first_iteration == TRUE) {  //setting the star time to zero.
            first_iteration = FALSE;
            clock_gettime(MY_CLOCK_TYPE, &start_time_val); start_realtime=realtime(&start_time_val);
        }
	
        // Release each service at a sub-rate of the generic sequencer rate

        printf("seqCnt (%2lld):", seqCnt);

        // Service_1 = RT_MAX-1	@ 33  Hz
        if ((seqCnt % 3) == 0)  { sem_post(&semS1); printf(" S1"); } //sem_post would unlock the semaphore.

        // Service_2 = RT_MAX-2	@ 16 Hz
        if ((seqCnt % 6) == 0)  { sem_post(&semS2); printf(" S2"); }

        // Service_3 = RT_MAX-3	@ 11 Hz
        if ((seqCnt % 9) == 0) { sem_post(&semS3); printf(" S3"); }

        printf("\n");

        seqCnt++;  //increment the index of the sequence counter

    } while (!abortTest && (seqCnt < threadParams->sequencePeriods));

    printf("Finishing Sequencer!\n");
    sem_post(&semS1); sem_post(&semS2); sem_post(&semS3);
    abortS1=TRUE; abortS2=TRUE; abortS3=TRUE;

    pthread_exit((void *)0);
}

void *Service_1(void *threadp)
{
    struct timespec current_time_val;
    double current_realtime;
    unsigned long long S1Cnt=0;
    threadParams_t *threadParams = (threadParams_t *)threadp;

    while(!abortS1)
    {
        sem_wait(&semS1);        // sem_wait, will wait here until the semaphore is unlock, by sem_post, in the sequencer.
        if (abortS1) { break; }
        S1Cnt++;

        clock_gettime(MY_CLOCK_TYPE, &current_time_val); current_realtime=realtime(&current_time_val);
        syslog(LOG_INFO, "[COURSE:2][ASSIGNMENT:7]: Thread %d start %lld @%6.9lf on core %d\n", threadParams->threadIdx, S1Cnt, current_realtime-start_realtime, sched_getcpu());

        // work load
        fibonacciForXms(TASK_DURATION); 
    }

    pthread_exit((void *)0);
}


void *Service_2(void *threadp)
{
    struct timespec current_time_val;
    double current_realtime;
    unsigned long long S2Cnt=0;
    threadParams_t *threadParams = (threadParams_t *)threadp;

    while(!abortS2)
    {
        sem_wait(&semS2);
        if (abortS2) { break; }
        S2Cnt++;

        clock_gettime(MY_CLOCK_TYPE, &current_time_val); current_realtime=realtime(&current_time_val);
        syslog(LOG_INFO, "[COURSE:2][ASSIGNMENT:7]: Thread %d start %lld @%6.9lf on core %d\n", threadParams->threadIdx, S2Cnt, current_realtime-start_realtime, sched_getcpu());

        // work load
        fibonacciForXms(TASK_DURATION); 
        fibonacciForXms(TASK_DURATION); 
    }

    pthread_exit((void *)0);
}

void *Service_3(void *threadp)
{
    struct timespec current_time_val;
    double current_realtime;
    unsigned long long S3Cnt=0;
    threadParams_t *threadParams = (threadParams_t *)threadp;

    while(!abortS3)
    {
        sem_wait(&semS3);
        if (abortS3) { break; }
        S3Cnt++;

        clock_gettime(MY_CLOCK_TYPE, &current_time_val); current_realtime=realtime(&current_time_val);
        syslog(LOG_INFO, "[COURSE:2][ASSIGNMENT:7]: Thread %d start %lld @%6.9lf on core %d\n", threadParams->threadIdx, S3Cnt, current_realtime-start_realtime, sched_getcpu());

        // work load
        fibonacciForXms(TASK_DURATION);
        fibonacciForXms(TASK_DURATION);
        fibonacciForXms(TASK_DURATION);
    }

    pthread_exit((void *)0);
}

double getTimeMsec(void)
{
  struct timespec event_ts = {0, 0};

  clock_gettime(CLOCK_MONOTONIC, &event_ts);
  return ((event_ts.tv_sec)*1000.0) + ((event_ts.tv_nsec)/1000000.0);
}

double realtime(struct timespec *tsptr)
{
    return ((double)(tsptr->tv_sec) + (((double)tsptr->tv_nsec)/1000000000.0));
}

void print_scheduler(void)
{
   int schedType;

   schedType = sched_getscheduler(getpid());

   switch(schedType)
   {
       case SCHED_FIFO:
           printf("Pthread Policy is SCHED_FIFO\n");
           break;
       case SCHED_OTHER:
           printf("Pthread Policy is SCHED_OTHER\n"); exit(-1);
         break;
       case SCHED_RR:
           printf("Pthread Policy is SCHED_RR\n"); exit(-1);
           break;
       case SCHED_DEADLINE:
           printf("Pthread Policy is SCHED_DEADLINE\n"); exit(-1);
           break;
       default:
           printf("Pthread Policy is UNKNOWN\n"); exit(-1);
   }
}

void fibonacciForXms(float timeMs)
{
    //long a = 0, b = 1, c = 0;
    double start_time = getTimeMsec(); 
    double end_time = start_time;
    while ((end_time - start_time) < timeMs) 
    {
        //c = a + b;
        //a = b;
        //b = c;
        end_time = getTimeMsec();
    }
    //printf("Execution time: %f - result: %lu\n", end_time - start_time, c); 
    //printf("Execution time: %f\n", end_time - start_time); 
}

/*
The expected output would be:
Dec 19 17:32:39 debian sequencer[2525]: [COURSE:2][ASSIGNMENT:7]: Linux debian 4.19.0-16-amd64 #1 SMP Debian 4.19.181-1 (2021-03-19) x86_64 GNU/Linux
Dec 19 17:32:39 debian sequencer[2525]: [COURSE:2][ASSIGNMENT:7]: Thread 1 start 1 @0.000102848 on core 1 
Dec 19 17:32:39 debian sequencer[2525]: [COURSE:2][ASSIGNMENT:7]: Thread 2 start 1 @0.010009083 on core 1 
Dec 19 17:32:39 debian sequencer[2525]: [COURSE:2][ASSIGNMENT:7]: Thread 3 start 1 @0.030981791 on core 1 
Dec 19 17:32:39 debian sequencer[2525]: [COURSE:2][ASSIGNMENT:7]: Thread 1 start 2 @0.031318173 on core 1 
Dec 19 17:32:39 debian sequencer[2525]: [COURSE:2][ASSIGNMENT:7]: Thread 1 start 3 @0.064310206 on core 1 
Dec 19 17:32:39 debian sequencer[2525]: [COURSE:2][ASSIGNMENT:7]: Thread 2 start 2 @0.074140269 on core 1 
Dec 19 17:32:39 debian sequencer[2525]: [COURSE:2][ASSIGNMENT:7]: Thread 1 start 4 @0.104451267 on core 1 

*/

/* The makefile
INCLUDE_DIRS = 
LIB_DIRS = 
CC=gcc

CDEFS=
CFLAGS= -O0 -g -Wall -Wextra  $(INCLUDE_DIRS) $(CDEFS)
LIBS= 

HFILES= 
CFILES= seqgen.c

SRCS= ${HFILES} ${CFILES}
OBJS= ${CFILES:.c=.o}

all:	seqgen  

clean:
	-rm -f *.o *.d
	-rm -f seqgen

seqgen: seqgen.o
	$(CC) $(LDFLAGS) $(CFLAGS) -o $@ $@.o -lpthread -lrt

depend:

.c.o:
	$(CC) $(CFLAGS) -c $<
*/
