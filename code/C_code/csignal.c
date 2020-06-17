
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

/** signals are a sw interruptions **/

/** signals are very useful for example when the program 
suddently stops, and you can have the change to close file handles,
free memory ... so you can get a consistant state before
your program ends, and you have the choice to fail gracefully**/

/** signals can also work for communication between threads **/

/** http://man7.org/linux/man-pages/man7/signal.7.html **/

/**
* the SIGCHLD signal is used to notify that a child process is finished
* the SIGBUS is a bus error
* the SIGSEGV is a segmentation violation
* the SIGFPE is a floating point error
* SIGUSR1 and SIGUSR2 are used to pass commands to a program
* SIGHUP is sometimes used to wake up an idling program or to reread its configurationfiles
* SIGTERM and SIGKILL are used to end a program.
* the difference between SIGTERM and SIGKILL, is that SIGTERM request the program to finish,
* so it is possible to do something, mask or even ignore the signal, whereas SIGKILL can not be 
* masked and just kills the process
**/

void handler(int num)
{
    write(STDOUT_FILENO, "I will not die!\n", 16);
}  

void seghandler(int num)
{
    write(STDOUT_FILENO, "Segmentation fault!!!\n",22); 
    abort();
/* in the signal handlers 'write' is used instead of printf, 
 the reason is that, signal handlers run asynchronously, meaning
 that they can interrupt the program flow at any given point, so
 in a signal hanlder async-safe functions are to be used */
/* http://man7.org/linux/man-pages/man7/signal-safety.7.html */
}

void aborthandler(int num)
{
    write(STDOUT_FILENO, "I die!!\n", 8);
}  


int main()
{
   signal(SIGINT,  handler);
   signal(SIGTERM, handler);    
   signal(SIGKILL, handler);
   signal(SIGSEGV, seghandler); 
   signal(SIGABRT, aborthandler);

   /** actually sigaction is prefered over the signal **/

   int i = 0;
   int *p = NULL;
   while(1)
   {
      printf("looping around %d \t -pid: %d\n", i, getpid());
      //trying to give value to a pointer that points to Null will cause a Segmentation fault.
      if (i == 1000) *p = 42; 
     
      ++i;
   }

   getchar(); 
   return 0; 
}
