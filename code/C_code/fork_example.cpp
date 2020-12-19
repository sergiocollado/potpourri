//to compile and run:
// g++ -std=c++11 -O -Wall main.cpp && ./a.out
// https://coliru.stacked-crooked.com/a/cd481c4c4a630b82

#include <iostream>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>

using namespace std;

int main()
{
	cout << "hello world!" <<endl;
	int pid = fork();
	if( pid == -1)
	{
		perror("fork"); 
	}
	else if(pid ==0)
	{
		//this is the child process
		sleep(3);
		cout << "Goodbye! - says the Child process" << endl;
		exit(1); //returns 1 - error. 
	}
	return(0);
}

// other reference: https://youtu.be/PZrQ4eGm-hM?list=PLfqABt5AS4FkW5mOn2Tn9ZZLLDwA3kZUY

/*
*  WHACHT OUT!: when using fork, you the parent process should wait for their child termination
*  otherwise, its memory will not be freed, and its memory not released, thus we would have a memory leak.
*  So the wait() function should be used.

 A child that terminates, but has not been waited for becomes a
       "zombie".  The kernel maintains a minimal set of information about
       the zombie process (PID, termination status, resource usage
       information) in order to allow the parent to later perform a wait to
       obtain information about the child.  As long as a zombie is not
       removed from the system via a wait, it will consume a slot in the
       kernel process table, and if this table fills, it will not be
       possible to create further processes. 
     
  reference: https://man7.org/linux/man-pages/man2/wait.2.html
*/
