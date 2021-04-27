// Compiled with: g++ -Wall -std=c++14 -pthread
// print the number with the putchar funtion

#include <iostream>
using namespace std;

void printNumber(int number){
  unsigned int numberarray[100] = {0,0,0,0,0,0,0,0,0,0};
  unsigned int i = 0;
  unsigned int number2 = 0;
    
  while(number >= 10) 
  {
    number2 = number % 10;
    number = number / 10;
    numberarray[i] = number2 + 48;
    ++i;
  }
  
  number = number % 10;
  numberarray[i] = number + 48;

  for( int j = i; j >= 0; --j)
  {
   putchar(numberarray[j]);   
  }
}

int main(){
    printNumber(1234567890);
    return 0;
}
