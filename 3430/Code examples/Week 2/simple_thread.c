// reminder - compile with -lpthread
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

struct Data {
    int id;
    int id2;
};

int aNumber = 1;


void* threading_task(void* ignored);

int main()
{
    pthread_t my_thread;

    // init the thread, runs it!
    pthread_create( &my_thread, NULL, threading_task, NULL);

    pthread_join(my_thread, NULL);
    printf("I'm back.\n");

    // back to the mainline
    printf("done\n");

}
void* threading_task(void* ignored)
{
    printf("Here I am!\n");
    printf("Nap time.\n");
    sleep(5);
    printf("I'm melting! melting! Oh, what a world! What a world!\n");

}