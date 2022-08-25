#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/types.h>
#include <stdatomic.h>

#define COUNT_UP_TO 100000000

void mutex_lock( atomic_flag * );
void mutex_unlock( atomic_flag * );

static atomic_flag lock = ATOMIC_FLAG_INIT;
static int counter = 0;

void *count_up( void *args ) {
    (void) args;

    for ( int i = 0; i < COUNT_UP_TO; i++ ) {
        mutex_lock( &lock );
        counter++;
        mutex_unlock( &lock );
    }

    return NULL;
}

int main( void ) {
    pthread_t p1, p2;

    pthread_create( &p1, NULL, count_up, NULL );
    pthread_create( &p2, NULL, count_up, NULL );

    pthread_join( p1, NULL );
    pthread_join( p2, NULL );
    printf( "Counter is %d\n", counter );
    return EXIT_SUCCESS;
}

void mutex_lock( atomic_flag *lock ) {  

    // return false if lock is free; true otherwise
    while(atomic_flag_test_and_set(lock)) {
        // spin
    }
    
    // while evaluated to false and lock was set to 1 (old value must be 1 now)
    assert(atomic_flag_test_and_set(lock) == 1);  
}

void mutex_unlock( atomic_flag *lock ) {

    // it was true that lock was 1 before; Assert that it is not free.
    assert(atomic_flag_test_and_set(lock) == 1);
    assert(atomic_flag_test_and_set(lock) != 0);
    atomic_flag_clear(lock );
}
