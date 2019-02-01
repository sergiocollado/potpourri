#include <stdio.h>
#include <stdlib.h> 

/*
* brief: this shows how to change the value of a const value.
* Usually the 'const' keyword prevent the change of its variable
* Actually the const, really goes for defining a 'read-only' value
* Another fact, is that a 'const' variable is stored in ROM, and not in RAM.
*/
int main(void) {
	
	printf("Hello wold!\n");
	
	const int myconstvar = 5;
	printf("my const value is: %d\n", myconstvar);
	
	int *pmyconstvalue = NULL;
	
	pmyconstvalue =(int*)&myconstvar; //if we not place a cast, it will complain
	*pmyconstvalue = 10;
	
	printf("my const value is: %d\n", myconstvar);
	
	exit(EXIT_SUCCESS);
}

/*** Output  *************************************************
Hello wold!
my const value is: 5
my const value is: 10
*************************************************************/
