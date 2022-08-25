// reminder - compile with -lpthread
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <limits.h> // for int max

// global variable
// what could possibly go wrong
int sum = 0;

void* threading_task(void* ignored)
{
    // max in divided by 2, one for each thread
    const int myAmount = INT_MAX/2;
    int i;
    int mysum = 0;
    for (i = 0; i < myAmount; i++)
        mysum = mysum + 1;


    //add lock here
    sum = sum + mysum;
    pthread_exit(0);
}


int main()
{
    pthread_t my_thread1;
    pthread_t my_thread2;

    printf("%d\n", INT_MAX);
    // init the thread
    pthread_create( &my_thread1, NULL, threading_task, NULL );
    pthread_create( &my_thread2, NULL, threading_task, NULL );

    pthread_join(my_thread1, NULL);
    pthread_join(my_thread2, NULL);

    // back to the mainline
    printf("done - total is %d, should be %d\n", sum, INT_MAX/2*2);
    printf("%f\n", (sum)/(float)INT_MAX);

}