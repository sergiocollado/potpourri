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
		sleep(3);
		cout << "Goodbye child!" << endl;
		exit(1);
	}
	return(0);
}
