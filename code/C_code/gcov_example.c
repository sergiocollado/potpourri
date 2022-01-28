#include <stdlib.h>
#include <stdio.h>

// Coverage example with gcov & lcov:

// To check the coverage, the compilation of the file
// have to use the flags: -fprofile-arcs -ftest-coverage 

// once compiled, for each source file compiled with the flag
// -fprofile-arcs, a .gcda profile output is created.

// to generate a report: gcov test.c

// for this example file:
// compile: gcc -fprofile-arcs -ftest-coverage test.c -o test
// ./test
// gcov test.c
// >File 'test.c'
// >Lines executed:78.57% of 14
// >Creating 'test.c.gcov'


// To use lcov: https://github.com/linux-test-project/lcov
// lcov --capture --directory . --output-file coverage.info # To generate the coverage.info data file

// >Capturing coverage data from .
// >Found gcov version: 7.5.0
// >Scanning . for .gcda files ...
// >Found 1 data files in .
// >Processing test.gcda
// >test.c:source file is newer than notes file '/home/sergio.gonzalez@jember.de/Documents/gcov_test/test.gcno'
// >(the message is displayed only once per source file)
// >Finished .info-file creation

// genhtml coverage.info --output-directory out # To generate a report from this data file

// >Reading data file coverage.info
// >Found 1 entries.
// >Found common filename prefix "/home/sergio.gonzalez@jember.de/Documents"
// >Writing .css and .png files.
// >Generating output.
// >Processing file gcov_test/test.c
// >Writing directory view page.
// >Overall coverage rate:
// >  lines......: 78.6% (11 of 14 lines)
// >  functions..: 75.0% (3 of 4 functions)

// To read the html report:
// firefox out

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

void function_3(void)
{
    printf("Function3 called\n");
}

int main() {

   function_1(10);
}
