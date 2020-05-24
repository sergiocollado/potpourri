/* reverse polish notation calculator: stack.c */

#include <stdio.h>
#include <stdlib.h>
#include "calc.h"
#define MAXVAL 100	/*max values in the stac */

static int    pp = 0;	/* position in the stack */
static double val[MAXVAL];

/* push: push value into the stack */
void push(double f)
{
  if (pp < MAXVAL)
    val[pp++] = f;
  else  {
    printf("ERROR: the stack is full, unable to push  %g\n", f);
    exit (1);
  }
}

/* pop: pops value out of the stack */
double pop(void)
{
  if(pp > 0)
    return val[--pp];
  else {
    printf("ERROR: empty stack, unable to pop\n");
    return 0.0;
  }
}
