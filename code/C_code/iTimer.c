/* Example code for setting
 * up an interval timer in 
 * Linux. 
 * 
 * Based on existing text example
 *
 * Original Text Source:-
 * Advanced Linux Programming
 * by CodeSourcery
 * */

#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>

void timer_handler (int signum)
{
 static int count = 0;
 struct timeval ts;

 count += 1;
 gettimeofday(&ts, NULL);
 printf ("%d.%06d: timer expired %d times\n", ts.tv_sec, ts.tv_usec, count);
}

int main ()
{
 struct sigaction sa;
 struct itimerval timer;

 /* Install timer_handler as the signal handler for SIGVTALRM. */
 memset (&sa, 0, sizeof (sa));
 sa.sa_handler = &timer_handler;
 sigaction (SIGVTALRM, &sa, NULL);

 /* Configure the timer to expire after 500 msec... */
 timer.it_value.tv_sec = 0;
 timer.it_value.tv_usec = 500000;
 /* ... and every 500 msec after that. */
 timer.it_interval.tv_sec = 0;
 timer.it_interval.tv_usec = 500000;
 /* Start a virtual timer. It counts down whenever this process is
   executing. */
 setitimer (ITIMER_VIRTUAL, &timer, NULL);

 /* Do busy work. */
 while (1);
}
