#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_cond_t cond;
pthread_mutex_t lock;

void *t0(void *param)
{
    pthread_mutex_lock(&lock);
    pthread_cond_wait(&cond, &lock);
    printf("t0 ready\n");
    pthread_mutex_unlock(&lock);
}
void *t1(void *param)
{
    pthread_mutex_lock(&lock);
    pthread_cond_wait(&cond, &lock);
    printf("t1 ready\n");
    pthread_mutex_unlock(&lock);
}
void *t2(void *param)
{
    pthread_mutex_lock(&lock);
    pthread_cond_wait(&cond, &lock);
    printf("t2 ready\n");
    pthread_mutex_unlock(&lock);
}

int main(void)
{
    pthread_t t[3];

    pthread_cond_init(&cond, NULL);
    pthread_mutex_init(&lock, NULL);

    pthread_create(&t[0], NULL, t0, NULL);
    pthread_create(&t[1], NULL, t1, NULL);
    pthread_create(&t[2], NULL, t2, NULL);

    usleep(1000); // Waiting for sub thread     

    pthread_cond_broadcast(&cond);

    pthread_join(t[0], NULL);
    pthread_join(t[1], NULL);
    pthread_join(t[2], NULL);
    pthread_cond_destroy(&cond);
    pthread_mutex_destroy(&lock);

}
