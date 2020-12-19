/* example of processes creation and signals */
/* based in: https://www.youtube.com/watch?v=3mkP_GAxKfs */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h> /*to use the alarm()*/
#include <string.h>
#include <signal.h> /*to use signals*/

void AlarmFunction(int);
void StopFunction(int);
void ContFunction(int);
void ChildFunction(int);

int processNumber = 0; //number of child processes.
pid_t pidArray[100]; //array of processes pids.
int ent = 0; //index of the processes array.
pid_t pid; //pid returned by fork()
pid_t parentPid = 0;
int i = 0;
   
int main(int argc, char *argv[])
{
   // processNumber = atoi(argv[1]); //to pass the number of processes as a parameter
   processNumber = 2; 
   
   for (i = 0; i < processNumber; ++i) // process creaton loop
   {
       pid = fork();
       if (pid == 0)
       {
           printf(">>> Children process created: %d - pid: %d, stopped and waiting for scheduling()\n", i, getpid());
           fflush(stdout); //to force the writing .... it could be better to use:    write(STDOUT_FILENO,
           
           //if (signal(SIGSTOP, StopFunction) == SIG_ERR)  //regiter signal handlers. 
           //{
           //    printf("error setting signal SIGSTOP\n");
              // The signals SIGKILL and SIGSTOP cannot be caught or ignored. -> https://linux.die.net/man/2/signal
           //}
           
           if (signal(SIGCONT, ContFunction) == SIG_ERR)
           {
                printf("error setting signal SIGCONT\n");
           }
           
           raise(SIGSTOP); // the children process stops, itself

           break; //children process gets out the loop. otherwise the children process would create other processes as well.
       }
       else 
       {
            parentPid = getpid();
            
            if (signal(SIGALRM, AlarmFunction)== SIG_ERR) //regiSter signal handlers in the parent process
            {
                 printf("error setting signal SIGALRM\n");
            }
       }
       pidArray[i] = pid;
   }
  
  if (parentPid == getpid())
  {
     printf("\nHello World!!! I'm the parent process: %d\n", getpid());   
  }
  
  usleep(100);
  
   if (i == processNumber) //only in the case (i == processsNumber), we are in the parent process. the child processes would have other values.
   {
    printf("-- Parent - pid: %d -> starts scheduling ... \n\n", getpid());
    ent = 0;
    
    int counter = 0;
    for (int j = 0; j < 3; ++j)  //parent exectuion loop
    {
        printf("\n\n=====================================\n");
        printf("\n (%d)>>> Parent launches child process %d - pid: %d\n", counter, ent, pidArray[ent]);
        i = ent;
        kill(pidArray[ent], SIGCONT); //requesT continue
        //alarm(X); //set alarm to call in X seconds
        ualarm(100, 0);  //https://www.man7.org/linux/man-pages/man3/ualarm.3.html
        printf("Parent awaits for alarm (with pause())\n");  fflush(stdout);
        pause(); //pause to wait for the alarm
        kill(pidArray[ent], SIGSTOP);
        printf("=====================================\n");
        ent = (ent+1) % processNumber;
        ++counter;
    }
    
    //terminate all the children
    for (int k = 0; k < processNumber; ++k)
    {
       kill(pidArray[k], SIGTERM);
    }
     
   }
   else 
   { //code that the children processes will execute.
    printf("\n...+++ children %d, - pid: %d - running ... \n", i, getpid());  fflush(stdout);
     while(1)
       {
          write(STDOUT_FILENO, ".",1);  
       }
   }
   
   exit(0);
}

void AlarmFunction(int)
{
   //write(STDOUT_FILENO, "\nALARM!!!\n",10);  
   printf("\n ALARM!! -> parent (%d) stops children: %d - pid: (%d)\n", getpid(), i, pidArray[ent]); 
   fflush(stdout); //to force the writing .... it could be better to use:    write(STDOUT_FILENO,
  /* we shouldn't use prinf : S */
  /* in the signal handlers 'write' is used instead of printf, 
 the reason is that, signal handlers run asynchronously, meaning
 that they can interrupt the program flow at any given point, so
 in a signal hanlder async-safe functions are to be used */
 /* http://man7.org/linux/man-pages/man7/signal-safety.7.html */ 
  kill(pidArray[ent], SIGSTOP); //requesT continue
}

void ContFunction(int)
{
   printf("\n CONTINUE!! in process - pid: (%d)\n", getpid());
   fflush(stdout);
}

void StopFunction(int)
{
   printf("\n STOP!! in process - pid: (%d)\n", getpid());
   fflush(stdout);
}

void ChildFunction(int)
{
   write(STDOUT_FILENO, "\nCHILD FINISHED!!!\n",19);  
}
/* about sigaction and signal: https://www.gnu.org/software/libc/manual/html_node/Signal-and-Sigaction.html */


/*
COMPILING: cc -std=c99 -Wall -pedantic main.cpp && ./a.out
LINK: 
SAMPLE OUTPUT: 

cc1plus: warning: command line option '-std=c99' is valid for C/ObjC but not for C++
>>> Children process created: 0 - pid: 26751, stopped and waiting for scheduling()

Hello World!!! I'm the parent process: 26750
-- Parent - pid: 26750 -> starts scheduling ... 



=====================================

 (0)>>> Parent launches child process 0 - pid: 26751
Parent awaits for alarm (with pause())

 CONTINUE!! in process - pid: (26751)
>>> Children process created: 1 - pid: 26752, stopped and waiting for scheduling()

 ALARM!! -> parent (26750) stops children: 0 - pid: (26751)
=====================================


=====================================

 (1)>>> Parent launches child process 1 - pid: 26752
Parent awaits for alarm (with pause())

 CONTINUE!! in process - pid: (26752)

 ALARM!! -> parent (26750) stops children: 1 - pid: (26752)
=====================================


=====================================

 (2)>>> Parent launches child process 0 - pid: 26751
Parent awaits for alarm (with pause())

 CONTINUE!! in process - pid: (26751)

...+++ children 0, - pid: 26751 - running ... 
......................................
 ALARM!! -> parent (26750) stops children: 0 - pid: (26751)
...=====================================

cc -std=c99 -Wall -pedantic main.cpp && ./a.out

*/
