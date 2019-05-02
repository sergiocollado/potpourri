//  to compile: gcc -lrt -std=c99 -g -Wall main.cpp && ./a.out 1 100
// -lrt is for linking the real time (rt) library(l)

// signals references: https://pubs.opengroup.org/onlinepubs/9699919799/basedefs/signal.h.html
// based on: http://man7.org/linux/man-pages/man2/timer_create.2.html
// ref: https://coliru.stacked-crooked.com/a/88dec034b807ab18

/*
 The program below takes two arguments: a sleep period in seconds, and
       a timer frequency in nanoseconds.  The program establishes a handler
       for the signal it uses for the timer, blocks that signal, creates and
       arms a timer that expires with the given frequency, sleeps for the
       specified number of seconds, and then unblocks the timer signal.
       Assuming that the timer expired at least once while the program
       slept, the signal handler will be invoked, and the handler displays
       some information about the timer notification.  The program
       terminates after one invocation of the signal handler.

       In the following example run, the program sleeps for 1 second, after
       creating a timer that has a frequency of 100 nanoseconds.  By the
       time the signal is unblocked and delivered, there have been around
       ten million overruns.

           $ ./a.out 1 100
            Establishing handler for signal 34
            Blocking signal 34
            timer ID is 0x22ae020
            Sleeping for 1 seconds
            Unblocking signal 34
            Caught signal 34
                sival_ptr = 0x7fffc6753890;     *sival_ptr = 0x22ae020
                overrun count = 10002811
*/

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <time.h>

#define CLOCKID CLOCK_REALTIME
#define SIG SIGRTMIN

#define errExit(msg)    do { perror(msg); exit(EXIT_FAILURE); \
                       } while (0)

static void print_siginfo(siginfo_t *si)
{
   timer_t *tidp;
   int tor;

   tidp = (timer_t *)si->si_value.sival_ptr;  

   printf("    sival_ptr = %p; ", si->si_value.sival_ptr);
   printf("    *sival_ptr = 0x%lx\n", (long) *tidp);

   tor = timer_getoverrun(*tidp);
   if (tor == -1)
       errExit("timer_getoverrun");
   else
       printf("    overrun count = %d\n", tor);
}

static void handler(int sig, siginfo_t *si, void *uc)
{
   /* Note: calling printf() from a signal handler is not safe
      (and should not be done in production programs), since
      printf() is not async-signal-safe; see signal-safety(7).
      Nevertheless, we use printf() here as a simple way of
      showing that the handler was called. */

   printf("Caught signal %d\n", sig);
   print_siginfo(si);
   signal(sig, SIG_IGN);
}

int
main(int argc, char *argv[])
{
   timer_t timerid;
   struct sigevent sev;
   struct itimerspec its;
   long long freq_nanosecs;
   sigset_t mask;
   struct sigaction sa;

   if (argc != 3) {
       fprintf(stderr, "Usage: %s <sleep-secs> <freq-nanosecs>\n",
               argv[0]);
       exit(EXIT_FAILURE);
   }

   /* Establish handler for timer signal */

   printf("Establishing handler for signal %d\n", SIG);
   sa.sa_flags = SA_SIGINFO;
   sa.sa_sigaction = handler;
   sigemptyset(&sa.sa_mask);
   if (sigaction(SIG, &sa, NULL) == -1)
       errExit("sigaction");

   /* Block timer signal temporarily */

   printf("Blocking signal %d\n", SIG);
   sigemptyset(&mask);
   sigaddset(&mask, SIG);
   if (sigprocmask(SIG_SETMASK, &mask, NULL) == -1)
       errExit("sigprocmask");

   /* Create the timer */

   sev.sigev_notify = SIGEV_SIGNAL;
   sev.sigev_signo = SIG;
   sev.sigev_value.sival_ptr = &timerid;
   if (timer_create(CLOCKID, &sev, &timerid) == -1)
       errExit("timer_create");

   printf("timer ID is 0x%lx\n", (long) timerid);

   /* Start the timer */

   freq_nanosecs = atoll(argv[2]);
   its.it_value.tv_sec = freq_nanosecs / 1000000000;
   its.it_value.tv_nsec = freq_nanosecs % 1000000000;
   its.it_interval.tv_sec = its.it_value.tv_sec;
   its.it_interval.tv_nsec = its.it_value.tv_nsec;

   if (timer_settime(timerid, 0, &its, NULL) == -1)
        errExit("timer_settime");

   /* Sleep for a while; meanwhile, the timer may expire
      multiple times */

   printf("Sleeping for %d seconds\n", atoi(argv[1]));
   sleep(atoi(argv[1]));

   /* Unlock the timer signal, so that timer notification
      can be delivered */

   printf("Unblocking signal %d\n", SIG);
   if (sigprocmask(SIG_UNBLOCK, &mask, NULL) == -1)
       errExit("sigprocmask");

   exit(EXIT_SUCCESS);
}
