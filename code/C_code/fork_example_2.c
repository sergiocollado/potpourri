/* example of processes */
/* based in: https://youtu.be/PZrQ4eGm-hM?list=PLfqABt5AS4FkW5mOn2Tn9ZZLLDwA3kZUY */
/* compile with: cc -std=c99 -Wall -pedantic main.cpp && ./a.out */
/* http://coliru.stacked-crooked.com/a/36a93558ef91a783 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h> /*to use the fork()*/
#include <sys/wait.h> /*to use wait()*/

   
int main(int argc, char *argv[])
{
    printf("Hello World!\n");
    int id=fork();
    if (id == -1) {
        printf("fork error");
        exit(1);
    }
    if (id == 0) {
        //this is the children process
        sleep(1);
    }
    printf("Current ID: %d, parent ID: %d\n", getpid(), getppid());
    
    int result = wait(NULL);
    if (result == -1) {
        printf("No children to wait for\n");
    } else {
        printf("process id:%d finished execution\n", result);
    }
    return 0;
}

/*
 SAMPLE OUTPUT:
 
Hello World!
Current ID: 25045, parent ID: 25044
No children to wait for
Hello World!
Current ID: 25044, parent ID: 25038
process id:25045 finished execution
 */
