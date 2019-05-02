#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

// to compile: g++ -std=c99 -lrt -g -Wall main.cpp && ./a.out

// references: 
// https://pubs.opengroup.org/onlinepubs/007904875/functions/alarm.html
// http://man7.org/linux/man-pages/man2/alarm.2.html
// https://coliru.stacked-crooked.com/a/6026f5eb312b3fa1

/* expected output

Hello!
1
2
3
4
5
Alarm signal sent!
6
7
8
9
Goodbye!

*/
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

static void alarmHandler(int signo);

int main(void){

    printf("Hello!\n");

    alarm(5);

    signal(SIGALRM, alarmHandler);

    for(int i = 1; i < 10; i++){
        printf("%d\n", i);
        sleep(1);    
    }

    printf("Goodbye!\n");

    return EXIT_SUCCESS;

}

static void alarmHandler(int signo)
{
    printf("Alarm signal sent!\n");
}
