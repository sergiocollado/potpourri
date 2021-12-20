//reference: https://docs.oracle.com/cd/E19205-01/820-0619/geosb/index.html

/*
The term 'deadlock' describes a condition in which two or more threads are blocked (hung) forever because they are waiting for each other.
There are many causes of deadlocks such as erroneous program logic, inappropriate use of synchronizations and barriers. 
This example focuses on deadlocks that are caused by the inappropriate use of mutual exclusion locks. 
This type of deadlock is commonly encountered in multi-threaded applications. 

The Dining Philosophers Scenario:

The dining philosophers scenario is a classic which is structured as follows. Five philosophers, numbered zero to four,
are sitting at a round table, thinking. As time passes, different individuals become hungry and decide to eat. There is
bowl of noodles on the table but each philosopher only has one chopstick to use. In order to eat, they must share chopsticks.
The chopstick to the left of each philosopher (as they sit facing the table) has the same number as that philosopher.

Each philosopher first reaches for his own chopstick which is the one with his number. When he has his assigned chopstick, 
he reaches for the chopstick assigned to his neighbor. After he has both chopsticks, he can eat.
After eating, he returns the chopsticks to their original positions on the table, one on either side.
The process is repeated until there are no more noodles.

An actual deadlock occurs when every philosopher is holding his own chopstick and waiting for the one from his neighbor to become available.
In this situation, nobody can eat and the philosophers are in a deadlock.
*/

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <assert.h>
#define PHILOS 5
#define DELAY 5000
#define FOOD 50
    
void *philosopher (void *id);
void grab_chopstick (int, int, char *);
void down_chopsticks (int, int);
int food_on_table ();

pthread_mutex_t chopstick[PHILOS];
pthread_t philo[PHILOS];
pthread_mutex_t food_lock;
int sleep_seconds = 0;


int main (int argn, char **argv)
{
    int i;

    if (argn == 2)
        sleep_seconds = atoi (argv[1]);

    pthread_mutex_init (&food_lock, NULL);
    for (i = 0; i < PHILOS; i++)
        pthread_mutex_init (&chopstick[i], NULL);
    for (i = 0; i < PHILOS; i++)
        pthread_create (&philo[i], NULL, philosopher, (void *)i);
    for (i = 0; i < PHILOS; i++)
        pthread_join (philo[i], NULL);
    return 0;
}

void* philosopher (void *num)
{
    int id;
    int i, left_chopstick, right_chopstick, f;

    id = (int)num;
    printf ("Philosopher %d is done thinking and now ready to eat.\n", id);
    right_chopstick = id;
    left_chopstick = id + 1;

    /* Wrap around the chopsticks. */
    if (left_chopstick == PHILOS)
        left_chopstick = 0;

    while (f = food_on_table ()) {

        /* Thanks to philosophers #1 who would like to take a nap
         * before picking up the chopsticks, the other philosophers
         * may be able to eat their dishes and not deadlock.  
         */
        if (id == 1)
            sleep (sleep_seconds);

        grab_chopstick (id, right_chopstick, "right ");
        grab_chopstick (id, left_chopstick, "left");

        printf ("Philosopher %d: eating.\n", id);
        usleep (DELAY * (FOOD - f + 1));
        down_chopsticks (left_chopstick, right_chopstick);
    }

    printf ("Philosopher %d is done eating.\n", id);
    return (NULL);
}

int food_on_table ()
{
    static int food = FOOD;
    int myfood;

    pthread_mutex_lock (&food_lock);
    if (food > 0) {
        food--;
    }
    myfood = food;
    pthread_mutex_unlock (&food_lock);
    return myfood;
}

void grab_chopstick (int phil,
                int c,
                char *hand)
   {
       pthread_mutex_lock (&chopstick[c]);
       printf ("Philosopher %d: got %s chopstick %d\n", phil, hand, c);
   }
   
   void
   down_chopsticks (int c1,
                    int c2)
   {
       pthread_mutex_unlock (&chopstick[c1]);
       pthread_mutex_unlock (&chopstick[c2]);
   }
