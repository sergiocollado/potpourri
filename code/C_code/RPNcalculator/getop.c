/* reverse polish notation calculator: getop.c*/

#include <stdio.h>
#include <ctype.h>  /*to classify chars*/
#include "calc.h"

int getch(void);
void ungetch(int);

/*getop: retrieves the next operator or numeric value*/
int getop(char s[])
{
    int i=0, c=0;
	
	while ((s[0] = c = getch()) == ' ' || c == '\t')
    {  ; /*empty positions*/ }
	
	s[1] = '\0';
	if ( !isdigit(c) && c != '.')
	    return c;      /*not a number*/
    if (isdigit(c))    /*get the integer part*/
      while(isdigit(s[++i] = c = getch()))
		{  /*keep getting digits*/}
    if (c == '.')      /*get the floating part*/
      while(isdigit(s[++i] = c = getch()))
		{  /*keep getting digits*/}
	s[i] = '\0';
	if (c != EOF) 
	    ungetch(c);
    return NUMBER;
} /*end getop()*/
