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

/*
 The sysconf() function provides a method for an
application to get values for system limits or variables. In this case the _SC_NPROCESSORS_CONF
argument asks for the number of processors configured
sysconfig() conforms to  POSIX.1-2001, POSIX.1-2008.

ref:
https://man7.org/linux/man-pages/man3/sysconf.3.html
*/
