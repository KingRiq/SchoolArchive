
#include <stdio.h>   // for printf, reading a file
#include <pthread.h> // pthread
#include <unistd.h>  // for sleep

struct threadInfo
{
    int aNumber;
};

void *work(void *ignored)
{

    printf("Thread has started\n");

    sleep(2);
    printf("Done!\n");
    pthread_exit(NULL);
}

int main()
{

    pthread_t thread;
    struct threadInfo threaddata;

    printf("I am %d\n", getpid());

    threaddata.aNumber = 42;

    printf("Starting\n");
    pthread_create(&thread, NULL, &work, NULL);

    pthread_join(thread, NULL);

    return 0;
}
