/* reverse polish notation calculator: getch.h*/

/* to get the characters that conform the number digits, 
   those are read up to the decimal point, or a non 
   numeric character, but at that point an extra character
   has already been readed. 
   getch() reads a character
   ungetch() returns the character to the input, so it can be got again */
   
#include <stdio.h>
#define BUFFER 100

static char buff[BUFFER];
static int  pbuf = 0;

/* getch- get a character*/
int getch(void)
{
    if (pbuf > 0)             /*if the buffer is not empty ...*/
	    return buff[--pbuf];   /* returns the character to the buffer*/
	else                      /*if the buffer is empty... */
	    return getchar();     /*reads a new character from input*/
}

/* ungetch- returns a character to the input*/
void ungetch(int c)
{
    if (pbuf >= BUFFER)
	    printf("ungetch- too many characters, buffer is full\n");
    else
	    buff[pbuf++]=c;
}
