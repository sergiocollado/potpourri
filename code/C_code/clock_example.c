#include <stdio.h>
#include <time.h>

int main(void) {
    
    clock_t tick, tack;
	
    tick = clock();
    printf("hola Mundo!\n");
    tack = clock();
    
    printf("tick: %d\n",(int)tick);
    printf("tack: %d\n",(int)tack);
    
    printf("aprox interval time: %f\n", (tack-tick)/(float)CLOCKS_PER_SEC );
    printf("aprox interval time: %f miliseconds\n", 1000*(tack-tick)/(float)CLOCKS_PER_SEC );
    return 0;
}
