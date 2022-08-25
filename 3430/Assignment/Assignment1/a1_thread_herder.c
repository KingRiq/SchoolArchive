//-----------------------------------------
// NAME: Eriq Hampton
// STUDENT NUMBER: 7852830
// COURSE: COMP 3430, SECTION: A01
// INSTRUCTOR: Robert Guderian
// ASSIGNMENT: Assignment 1, QUESTION: 3
//
// REMARKS: Creates/Deletes n threads via signals and config file 
//-----------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>
#include "a1_thread_herder.h"



pthread_t* workers = NULL;
int volatile count = 0;

int main(void) {
    signal(SIGHUP, sighup_handler);
    signal(SIGINT, sigint_handler);
    signal(SIGUSR2, sigusr2_handler);
    int nums;
    
    printf("Hello I am the Parent [ID: %d]\n", getpid());
    nums = read_file();
    create(nums);

    //wait until every thread is cleaned properly
    while(count > 0);
    
    printf("No more threads to herd! Time to terminate.\n");
    printf("Process Complete\n");

    exit(EXIT_SUCCESS);
}

//------------------------------------------------------
// read_file
//
// PURPOSE: Reads config.txt
// INPUT PARAMETERS:
//     None
// OUTPUT PARAMETERS:
//     int nums - returned so the main process knows what the config file says
//------------------------------------------------------
int read_file() {
    char *filename = "config.txt";
    int fd = open(filename, O_RDONLY);
    char configtext[3]; 
    int nums;

    assert(fd > 0);
    printf("Reading Config File!\n");
    read(fd, &configtext, 4);
    close(fd);
    
    printf("Changing settings to %d\n",atoi(configtext));
    nums = atoi(configtext);
    
    // negative ints should fail
    assert(nums >= 0);
    
    return nums;
}

//------------------------------------------------------
// create
//
// PURPOSE: Creates n threads and sends them to be configured. 
// Issues an ID and keeps track of it in global variable count.
//
// INPUT PARAMETERS:
//     int thread_Num; Which is the number initially inside config.txt
// REMARKS: Exit failure on failed thread creation
//------------------------------------------------------
void create(int thread_Num){

    workers = (pthread_t*) malloc(thread_Num * sizeof(pthread_t));

    // create n children
    printf("Creating %d threads.\n", thread_Num);
    for(int i = 0; i < thread_Num; i++) {
        
        printf("Starting Thread [ID: %d]\n" , i);
        if(pthread_create(&workers[i], NULL, &work, &i) != 0) {
            perror("Thread creation unsuccessful. EXIT\n");
            exit(EXIT_SUCCESS);

        }
        usleep(500);
    }
    count += thread_Num;

    // print Parent ID at the bottom
    print();
    wait_prompt();
}

//------------------------------------------------------
// work
//
// PURPOSE: Configures processes to the appropriate signals
//     and runs them indefinitely until given permission by the main process
//     to exit.
// INPUT PARAMETERS:
//     void tiD (thread ID). Keeps track of the id passed for printing.
// OUTPUT PARAMETERS:
//     None
//------------------------------------------------------
void* work(void* tID) {

    // mask the expected signals
    sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGINT);
    sigaddset(&mask, SIGHUP);
    pthread_sigmask(SIG_BLOCK, &mask, NULL);
    
    int* thread_ID = (int*) tID;
    printf("Child Thread [ID: %d] started!\n", *thread_ID);

    // sleep indefinitely
    while(1) {
        sleep(1);
    }

    // compiler requires this but never runs
    pthread_exit(EXIT_SUCCESS);
}

//------------------------------------------------------
// updateCount
//
// PURPOSE: reads config file then decides to increase 
// or decrease based on what was read
//
// INPUT PARAMETERS:
//     None
// OUTPUT PARAMETERS:
//     None
//------------------------------------------------------
void updateCount() {

    // read the config file and collect the difference
    int temp = read_file();
    int difference = temp - count;
    
    // determine if we are increasing, decreasing, or doing nothing
    if(difference > 0) {

        increase(difference);
    }
    else if(difference < 0) {
        
        difference = count - temp;
        decrease(difference);
    }
    else {

        printf("There are already this many threads.\n");
    }

    // print Parent ID at the bottom
    print();
    wait_prompt();
}

//------------------------------------------------------
// increase
//
// PURPOSE: Reallocates worker array and increase number of current workers by n (nums) 
// and sends them to be configured for work.
// INPUT PARAMETERS:
//     int nums - represents the number of threads we need to create
// OUTPUT PARAMETERS:
//     None
// REMARKS: This is different from create because we must
//     realloc memory and nums represents how many more
//     threads we need to create.
//------------------------------------------------------
 void increase(int nums) {

    // we need to realloc to increase size
    workers = realloc(workers, (nums+count+1) * sizeof(pthread_t));
    
    // start at newest index
    printf("Creating %d threads.\n", nums);
    for(int i = count; i < count + nums; i++) {
        
        printf("Starting Thread [ID: %d]\n" , i);
        if(pthread_create(&workers[i], NULL, &work, &i) != 0) { 
            
            perror("Thread creation unsuccessful. EXIT\n");
            exit(EXIT_FAILURE);
        }
        usleep(500);
    }
    count += nums;
}

//------------------------------------------------------
// decrease
//
// PURPOSE: Decreases number of current workers by n (nums) and reallocates worker array.
// and sends them to be configured for work.
// INPUT PARAMETERS:
//     int nums - represents the number of threads we need to remove
// OUTPUT PARAMETERS:
//     None
//------------------------------------------------------
void decrease(int nums) {

    int lower_bound = count-nums;
    printf("Removing %d threads.\n", nums);
    
    if(lower_bound > -1) {
        for(int i = count-1; i > lower_bound-1; i--) {
            
            // Kill Slowly
            printf("Killing CHILD Thread [ID: %d]\n", i);
            pthread_kill(workers[i],SIGUSR2);

            // wait until that thread exits and enforce that it did
            pthread_join(workers[i], NULL);
            count--;       
        }     
    }

    workers = realloc(workers, ((count)+1));
    
    // no threads means we are free to exit
    if(count == 0) {
        free(workers);
    }     
}

//------------------------------------------------------
// sigint_handler
//
// PURPOSE: SIGINT handler representing communication for parent process
//     to close all non-main threads.
// INPUT PARAMETERS:
//     None
// OUTPUT PARAMETERS:
//     None
//------------------------------------------------------
void sigint_handler() {
    // kill all processes and exit safely
    killAll();
}

//------------------------------------------------------
// sighup_handler
//
// PURPOSE: Handles SIGHUP signal and updates the number currently working threads
// INPUT PARAMETERS:
//     None
// OUTPUT PARAMETERS:
//     None
//------------------------------------------------------
void sighup_handler() {
    updateCount();
}
//------------------------------------------------------
// sigusr2_handler
//
// PURPOSE: Handles SIGUSR2 which is the signal received 
//  from parent process to close a particular thread
// INPUT PARAMETERS:
//     None
// OUTPUT PARAMETERS:
//     None
//------------------------------------------------------
void sigusr2_handler() {

    printf("Thread %d killed!\n", count-1);
    pthread_exit(EXIT_SUCCESS);
    
}

//------------------------------------------------------
// killall()   
//
// PURPOSE: Sends all threads to be killed
// INPUT PARAMETERS:
//     None:
// OUTPUT PARAMETERS:
//     None
//------------------------------------------------------
void killAll() {

    assert(count > 0);
    printf("We are going to close all threads now!\n");
    decrease(count);
    assert(count == 0);
}

//------------------------------------------------------
// wait_prompt
//
// PURPOSE: Used to print Parent Process with ID and let user know
//     the Parent process is still waiting.
// INPUT PARAMETERS:
//     None
// OUTPUT PARAMETERS:
//     None
//------------------------------------------------------
void wait_prompt() {
    printf("Parent Process [ID: %d] waiting... \n", getpid());
}

//------------------------------------------------------
// print
//
// PURPOSE: Prints the Child process IDs in a list for viewing
// INPUT PARAMETERS:
//     None
// OUTPUT PARAMETERS:
//     None
//------------------------------------------------------
void print() {

    printf("\nProcess ID's of children\n");
    printf("---------------------------\n");
    for(int i = 0; i < count; i++) {

        printf("Child Thread [ID: %d]\n", i);
    }
    printf("---------------------------\n\n");
}
