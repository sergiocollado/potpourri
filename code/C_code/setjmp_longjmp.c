/**
Use setjmp and longjmp functions from the <setjmp.h> header file. You can use setjmp to save the current state of the program and longjmp to jump back to the saved state.
**/

#include <setjmp.h> 
#include <stdio.h> 
 
jmp_buf buf; 
 
void func() { 
  printf("func() after longjmp\n"); 
} 
 
int main() { 
  int val; 
  val = setjmp(buf); 
  if (val == 0) { 
    printf("First time through\n"); 
    longjmp(buf, 1); 
  } else { 
    func(); 
  } 
  return 0; 
} 
