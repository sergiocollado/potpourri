#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/*

Given a big integer (represented as a sequence of bytes) a and an 8-bit unsigned integer b,
implement a function that calculates the (integer) quotient  a / b and the remainder a % b.
For example, 0xa07cf710 / 0x37 = 0x02eaffd6 and 0xa07cf710 % 0x37 = 0x16.

0xa07cf710a07cf710a07cf710a07cf710a07cf710

501 (dividend) by 4 (divisor) with a result of 125 (quotient) and 1 (remainder):

 501 ÷ 4 = 125 R 1
-4         ( 4 ×  1 =  4) => 1 becomes the leftmost quotient digit
 10        ( 5 -  4 =  1) => 1 remains, bring down the next digit in the dividend
 -8        ( 4 ×  2 =  8) => 2 becomes the second leftmost quotient digit
  21       (10 -  8 =  2) => 2 remains, bring down the next digit in the dividend
 -20       ( 4 ×  5 = 20) => 5 becomes the third leftmost quotient digit
   1       (21 - 20 =  1) => 1 becomes the remainder

*/

int main() {
    char dividend[] = {0x0a}; //, 0xa0 0x7c, 0xf7, 0x10};
    long int dividend_size = 1;
    char divisor = 0x03; //0x37;
    char quotient[100] = {0}; 
    memset(quotient, 0x00, 100 );
    char reminder = 0;
    (void) quotient;
    (void) reminder; 
    char local_dividend  = 0;
    
    for( long int counter = 0; counter != dividend_size; counter++) 
    {
        char result = 0;
        local_dividend = local_dividend*10 + dividend[counter];
        int  digit = 0; 
        do
        {
            digit += 1;
            result = local_dividend - divisor;  
            
            printf("local_divident: '%d'\n", (int)local_dividend);
            printf("result: '%d'\n", (int)result);
            if (result <= 0) {
                
                break;
            }
            local_dividend = result;
        }while( result > 0);
        quotient[counter] = local_dividend;
        printf("quotient[counter]: '%d'\n", (unsigned)quotient[counter]);
   
    }
    


    return 0;
}
