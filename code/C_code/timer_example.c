//Based on the example of the article: The Use of POSIX in Real-time Systems, Assessing its Effectiveness and Performance

#include <signal.h>
#include <time.h>

void timer_create(int num_secs, int num_nsecs)
{
 struct sigaction sa;
 struct sigevent sig_spec;
 sigset_t allsigs;
 struct itimerspec tmr_setting;
 timer_t timer_h;
  
 /* setup signal to respond to timer */
 sigemptyset(&sa.sa_mask);
 sa.sa_flags = SA_SIGINFO;
 sa.sa_sigaction = timer_intr;
 if (sigaction(SIGRTMIN, &sa, NULL) < 0 ) { perror(“sigaction”); }
 sig_spec.sigev_notify = SIGEV_SIGNAL;
 sig_spec.sigev_signo = SIGRTMIN;
  
 /* create timer, which uses the REALTIME clock */
 if (timer_create(CLOCK_REALTIME,&sig_spec,&timer_h) < 0 )
 perror(“timer create”);
  
 /* set the initial expiration and frequency of timer */
 tmr_setting.it_value.tv_sec = 1;
 tmr_setting.it_value.tv_nsec = 0;
 tmr_setting.it_interval.tv_sec = num_secs;
 tmr_setting.it_interval.tv_sec = num_nsecs;
 if (timer_settime(timer_h,0,&tmr_setting,NULL) < 0 ) { perror(“settimer”); }
  
 /* wait for signals */
 sigemptyset(&allsigs);
 while ( 1 ) { sigsuspend(&allsigs); }
}

/* routine that is called when timer expires */
void timer_intr(int sig, siginfo_t *extra, void *cruft)
{
 /* perform periodic processing and then exit */
}
