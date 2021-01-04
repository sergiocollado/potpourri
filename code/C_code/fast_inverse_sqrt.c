// FAST INVERSE SQRT
//reference: https://en.wikipedia.org/wiki/Fast_inverse_square_root#:~:text=Fast%20inverse%20square%20root%2C%20sometimes,IEEE%20754%20floating%2Dpoint%20format.
//reference: https://youtu.be/p8u_k2LIZyo
//reference: http://coliru.stacked-crooked.com/a/056cac1662fa463f

#include <iostream>
#include <math.h>

float Q_rsqrt( float number )
{
    // for all number: 0 =< number =< 1
	long i;
	float x2, y;
	const float threehalfs = 1.5F;

	x2 = number * 0.5F;
	y  = number;
	i  = * ( long * ) &y;                       // evil floating point bit level hacking
	i  = 0x5f3759df - ( i >> 1 );               // what the fuck? 
	y  = * ( float * ) &i;
	y  = y * ( threehalfs - ( x2 * y * y ) );   // 1st iteration
//y  = y * ( threehalfs - ( x2 * y * y ) );   // 2nd iteration, this can be removed

	return y;
}

int main()
{
 float number =  0.15625;   //number must be in the range [0,1]
 float result = Q_rsqrt(number);
 printf("fast inverse sqrt of %2.5f is: %f\n", number, result);
}
