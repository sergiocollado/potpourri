// Example program
// uses sysconf() function to determine how many
// processors are available to the OS.

#include <unistd.h>
#include <iostream>

using namespace std;

int main(int argc,char *argv[])
{
 cout << "number of processors: " << sysconf(_SC_NPROCESSORS_CONF) <<endl;
 return(0);
} 
