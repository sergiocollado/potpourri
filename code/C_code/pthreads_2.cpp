// to compile:
// g++ -std=c++11 -pthread  -Wall -pedantic -pthread main.cpp && ./a.out
// 
// ref
// http://coliru.stacked-crooked.com/a/ea9544db3f686a6d
// 
// the expected result:
// Hello World! from GCC 8.2.0
// this is the main program
// hello I am a thread running! thread2
// hello I am a thread running! thread1
// thread 1 finished OK
// thread 2 finished OK

#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <pthread.h>

void *my_thread_function(void *arg)
{
    //do my stuff
    char *my_passed_string = (char *)arg;
    std::cout << "hello I am a thread running! "<<  my_passed_string << std::endl;
    return NULL;
}


int main()
{
    pthread_t thread_Id1, thread_Id2;

    const char my_string1[]= "thread1"; int result1 = 0; void *exit_status1;
    const char my_string2[]= "thread2"; int result2 = 0; void *exit_status2;
    
    std::cout << "Hello World!" << " from GCC " << __VERSION__ << std::endl;
    
    //create a thread-
   result1 =  pthread_create( &thread_Id1, NULL, my_thread_function, (void *)my_string1);
   if(result1)
   {
     std::cout << "Error - pthread_create() return code: "<< result1 << std::endl;
     exit(EXIT_FAILURE);
   }

    //create a second thread-
   result2 =  pthread_create( &thread_Id2, NULL, my_thread_function, (void *)my_string2);
   if(result1)
   {
     std::cout << "Error - pthread_create() return code: "<< result2 << std::endl;
     exit(EXIT_FAILURE);
   } 

    //the main program continues, while the thread executes
    std::cout << "this is the main program" << std::endl;
      
    //wait to join the pthreads
    pthread_join( thread_Id1, &exit_status1);
    pthread_join( thread_Id2, &exit_status2);    
    
    if( exit_status1 == 0) std::cout << "thread 1 finished OK" << std::endl;
    if( exit_status2 == 0) std::cout << "thread 2 finished OK" << std::endl;
    
    //now only runs the main program.
    return EXIT_SUCCESS;
}
