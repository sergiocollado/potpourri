#include <stdio.h>
#include <unistd.h>
#include <sys/timerfd.h>
#include <sys/epoll.h>

#define MAX_EVENTS 10

int main(int argc, char **argv)
{
    int timerfd;
    struct timespec now;
    struct itimerspec new;

    int epoll_fd;
    struct epoll_event event, events[MAX_EVENTS];
    event.events = EPOLLIN | EPOLLET;
    event.data.fd = timerfd;
  
    printf("Test system timer by printing hello repeatly.\n");
    printf("We use epoll util to notice timer expiring.\n");

    epoll_fd = epoll_create(1);
    if(epoll_fd == -1) 
    {   
        perror("epoll create.");
        return -1; 
    }   
    
    timerfd = timerfd_create(CLOCK_REALTIME, TFD_NONBLOCK);
    if(timerfd == -1) 
    {   
        fprintf(stderr, "create timerfd failed.\n");
        return -1; 
    }   
    
    if(clock_gettime(CLOCK_REALTIME, &now) == -1) 
    {   
        fprintf(stderr, "get time failed.\n");
        return -1; 
    }   

    new.it_value.tv_sec = now.tv_sec + 1;
    new.it_value.tv_nsec = now.tv_nsec;
    new.it_interval.tv_sec = 2;
    new.it_interval.tv_nsec = 0;

    if(timerfd_settime(timerfd, TFD_TIMER_ABSTIME, &new, NULL) == -1) 
    {   
        fprintf(stderr, "timerfd_settime failed.\n"); 
        return -1; 
    }   
    

    if(epoll_ctl(epoll_fd, EPOLL_CTL_ADD, timerfd, &event) == -1)
    {
        perror("epoll_ctl");
        return -1;
    }

    for(;;)
    {
        int nfds = epoll_wait(epoll_fd, events, MAX_EVENTS, -1);
        if(nfds == -1)
        {
            perror("epoll_wait");
            return -1;
        }
        int n;
        for(n = 0; n < nfds; n++)
        {
            if(events[n].data.fd == timerfd)
            {
                printf("hello.\n");
                //we must read timerfd here.
                long long exp;
                read(timerfd, &exp, sizeof(long long));
            }
        }
    }

}
 
