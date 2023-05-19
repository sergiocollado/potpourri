// to compile:
// g++ -std=c++11 -pthread  -Wall -pedantic -pthread main.cpp && ./a.out
// reference:
// http://coliru.stacked-crooked.com/a/df0e415373fee04b
// expected output:
//
// Hello World! from GCC 8.2.0
// this is the main program
// hello I am a thread running!
// ----------------------------------------
// references  Multithreaded Programming Guide: https://docs.oracle.com/cd/E19455-01/806-5257/index.html 

#include <iostream>
#include <string>
#include <vector>
#include <pthread.h>

void *my_thread_function(void *arg)
{
    //do my stuff
    std::cout << "hello I am a thread running!"<< std::endl;
    return NULL;
}


int main()
{
    pthread_t thread_Id;
    void *exit_status;
    int arguments;
    arguments = 42;
    
    std::cout << "Hello World!" << " from GCC " << __VERSION__ << std::endl;
    
    //create a thread-
    pthread_create( &thread_Id, NULL, my_thread_function, &arguments);
    
    //the main program continues, while the thread executes
     std::cout << "this is the main program" << std::endl;
      
    //wait to join the pthreads
    pthread_join( thread_Id, &exit_status);
    
    //now only runs the main program.
    return 0;
}
