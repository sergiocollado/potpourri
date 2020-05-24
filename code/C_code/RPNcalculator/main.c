/* reverse polish notation calculator*/

/* the program request input in RPN reverseh polish notation
   up to the EOF (end of file) character, that is end of file or Ctrl+D).
   Example:
    (10-8)*(4+5)
   this is writen as:
    10 8 - 4 5 + *
*/

#include <stdio.h>
#include <stdlib.h> //to use atof()
#include "calc.h"

#define MAXOP  100 /*max number of operands and operators*/
#define NUMBER '0' /*key to detect number*/

int    getop(char[]);
void   push (double);
double pop  (void);

/*main program*/
void main(void){
	
	int type;
	double op2;
	char s[MAXOP];
	
	printf("\nREVERSE POLISH NOTATION CALCULATOR\n");
	printf("enter expressions in reverse polish notation.\n");
	printf("To finish, use: Ctrl+D\n");	
	
	while((type = getop(s)) != EOF) {
		switch(type) {
			case NUMBER:
			    push(atof(s));
				break;
		    case '+':
			    push(pop()+pop());
				break;
		    case '*':
			    push(pop()*pop());
				break;
		    case '-':
			    op2 = pop();
				push(pop() - op2);
				break;
			case '/':
			    op2 = pop();
				if(op2 != 0.0)
				    push(pop()/op2);
			    else
				   printf("ERROR: null division\n");
                break;
			case '\n':
                printf("Result:\t%.8g\n",pop());
                break;
            default:
                printf("ERROR: unknwon command\n");
                break;				
		} /*end switch*/

	} /*end of while()*/
	return;
} /*end main*/
