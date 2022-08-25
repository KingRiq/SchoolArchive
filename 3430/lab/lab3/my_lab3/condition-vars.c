#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/types.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>


#define MAX_BUFFER_SIZE 4096

void * toLowercase(void *);
void *toUppercase(void *);
void update_Buffer(char * , char*);

char user_Input[MAX_BUFFER_SIZE];
pthread_mutex_t buffer_Lock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t thread_Lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t main_Signal = PTHREAD_COND_INITIALIZER;
pthread_cond_t thread_Signal = PTHREAD_COND_INITIALIZER;
pthread_t p1, p2;

int main( void ) {
    char temp[MAX_BUFFER_SIZE];
    printf("Please enter text. To exit press CTRL+D\n");
    
    
    while (NULL != fgets(temp, sizeof(temp), stdin)) {

        // lock and start thread1
        update_Buffer(user_Input, temp);
        pthread_create( &p1, NULL, toLowercase, &user_Input);
        
        //wait for child to wait
        pthread_cond_wait(&main_Signal, &buffer_Lock);    // ensure child is ready to hear signal
        pthread_mutex_unlock(&buffer_Lock);
        usleep(500);
        pthread_cond_signal(&main_Signal);

    }
    printf("Process Complete\n");
    return EXIT_SUCCESS;
}

void *toLowercase(void* var) {
    char line[MAX_BUFFER_SIZE];

    // let main know you are ready to wait and wait for signal
    pthread_cond_signal(&main_Signal);
    pthread_mutex_lock(&buffer_Lock);
    
    //give up the lock to wait for main
    pthread_cond_wait(&main_Signal, &buffer_Lock);
    
    //process work
    strcpy(line, (char*) var);
    pthread_mutex_unlock(&buffer_Lock);
    
    // thread_Lock lets us know that thread2 is still waiting on us to signal
    pthread_mutex_lock(&thread_Lock);
    pthread_create( &p2, NULL, toUppercase, &line);
    
    // no locks needed here
    for(int i = 0; line[i]; i++) {
        line[i] = tolower(line[i]);
    }

    //acquire and update buffer
    update_Buffer(user_Input, line);
    printf("Lowercase: %s", user_Input);
    pthread_mutex_unlock(&buffer_Lock);
    
    
    //give up thread_lock, wait for thread2 to signal it is waiting, signal it to proceed, then unlock
    pthread_cond_wait(&thread_Signal, &thread_Lock);
    pthread_mutex_unlock(&thread_Lock);
    pthread_cond_signal(&thread_Signal);
    
    return NULL;
}

void *toUppercase(void* var) {
    char line[MAX_BUFFER_SIZE];
    strcpy(line, (char*) var);  

    //try to acquire thread locks and signal when you do
    pthread_mutex_lock(&thread_Lock);
    pthread_cond_signal(&thread_Signal);

    // wait for signal from thread1 before proceeding
    pthread_cond_wait(&thread_Signal, &thread_Lock);  
    pthread_mutex_unlock(&thread_Lock);
    
    
    for(int i = 0; line[i]; i++) {
        line[i] = toupper(line[i]);
    }
    
    //acquire and update buffer
    update_Buffer(user_Input, line);
    printf("UpperCase: %s", user_Input);
    pthread_mutex_unlock(&buffer_Lock);
    
    return NULL;
}

// obtain the lock and change the buffer
void update_Buffer(char* old, char* new) {
    pthread_mutex_lock(&buffer_Lock);
    strcpy(old, new);
}
