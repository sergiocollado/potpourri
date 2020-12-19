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
*/
