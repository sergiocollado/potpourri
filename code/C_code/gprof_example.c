#include <stdlib.h>
#include <stdio.h>

// compiles with: gcc -pg test.c -o test 
// the -pg flag, is to profile with gprof

// once compiled, it will be created a file gmon.out
// to check the profiling
// gprof test gmon.out > analysis.txt

void function_2(const int value)
{
    for(int j = 0; j < value; ++j)
    { printf("\t %d\n",j); }

}

void function_1(const int value)
{
    for(int i = 0; i < value; ++i)
    {
        function_2(10);
        printf("function_1 %d\n", i);
    }
}


int main() {

   function_1(10);
}

/* Example of the output analysis

Flat profile:

Each sample counts as 0.01 seconds.
 no time accumulated

  %   cumulative   self              self     total           
 time   seconds   seconds    calls  Ts/call  Ts/call  name    
  0.00      0.00     0.00       10     0.00     0.00  function_2
  0.00      0.00     0.00        1     0.00     0.00  function_1

 %         the percentage of the total running time of the
time       program used by this function.

cumulative a running sum of the number of seconds accounted
 seconds   for by this function and those listed above it.

 self      the number of seconds accounted for by this
seconds    function alone.  This is the major sort for this
           listing.

calls      the number of times this function was invoked, if
           this function is profiled, else blank.

 self      the average number of milliseconds spent in this
ms/call    function per call, if this function is profiled,
	   else blank.

 total     the average number of milliseconds spent in this
ms/call    function and its descendents per call, if this
	   function is profiled, else blank.

name       the name of the function.  This is the minor sort
           for this listing. The index shows the location of
	   the function in the gprof listing. If the index is
	   in parenthesis it shows where it would appear in
	   the gprof listing if it were to be printed.
*/
