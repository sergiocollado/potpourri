#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<stdbool.h>

long int p, q, n, t, flag,  j, i, icounter; // en[100],e[100], d[100], temp[100],m[100],
long int en[100], e[100], d[100], temp[100];
char m[100];
// p is the first prime number
// q is the second prime number

char msg[100];
bool set_q(long int);
long int get_q(void); 
int prime(long int);
void ce();
long int cd(long int);
void encrypt();
void decrypt();
