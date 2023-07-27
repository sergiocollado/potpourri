// reference: https://gist.github.com/shelterz/4b13459668eec743f15be6c200aa91b2

#include <stdio.h>
#include <pthread.h>

#define THREAD_NUMS 4
pthread_barrier_t barrier;

void *t0(void *param)
{
    pthread_barrier_wait(&barrier);
    printf("t0 ready\n");
}
void *t1(void *param)
{
    pthread_barrier_wait(&barrier);
    printf("t1 ready\n");
}
void *t2(void *param)
{
    pthread_barrier_wait(&barrier);
    printf("t2 ready\n");
}

int main(void)
{
    pthread_t t[3];

    pthread_barrier_init(&barrier, NULL, THREAD_NUMS);

    pthread_create(&t[0], NULL, t0, NULL);
    pthread_create(&t[1], NULL, t1, NULL);
    pthread_create(&t[2], NULL, t2, NULL);

    pthread_barrier_wait(&barrier);
    printf("all sub threads ready, go!\n");

    pthread_barrier_destroy(&barrier);

}
