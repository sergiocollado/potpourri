/* reverse polish notation calculator: calc.h*/

#define NUMBER '0'
void   push(double);   /*push into the stack*/
double pop(void);      /*pops out from the stack*/
int    getopt(char[]);
int    getch(void);
void   ungetch(int);
