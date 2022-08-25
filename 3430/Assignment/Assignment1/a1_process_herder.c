//-----------------------------------------
// NAME: Eriq Hampton
// STUDENT NUMBER: 7852830
// COURSE: COMP 3430, SECTION: A01
// INSTRUCTOR: Robert Guderian
// ASSIGNMENT: Assignment 1, QUESTION: 2
//
// REMARKS: Creates/Deletes n processes via signals and config file
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
#include "a1_process_herder.h"

int volatile count = 0;
pid_t* children = NULL;

int main(void) {
    signal(SIGHUP,sighup_handler);
    signal(SIGINT,sigint_handler);
    
    // Intro
    printf("Hello I am the Parent Process [ID: %d]!\n\n", getpid());
    count = read_file();
    create(count);
    
    // Wait until there are no workers left
    while(wait(NULL) > 0);

    printf("No more processes to herd! Time to terminate.\n");
    printf("Process Complete.\n");
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

    // ensure file opened successfully
    assert(fd > 0);
    printf("Reading Config File!\n");
    read(fd, &configtext, 4);
    close(fd);
    
    nums = atoi(configtext);
    printf("Changing settings to %d\n",nums);

    // negative ints should fail
    assert(nums >= 0);

    return nums;
}

//------------------------------------------------------
// create
//
// PURPOSE: Creates n processes specified in the config file and sends them to be configured. 
// INPUT PARAMETERS:
//     int proc_Num (process number); Which is the number initially inside config.txt
// 
// OUTPUT PARAMETERS:
//     None
// REMARKS: Exit failure on failed process creation
//------------------------------------------------------
void create(int proc_Num){

    children = (pid_t*) malloc(proc_Num * sizeof(pid_t));

    // create n children
    printf("Creating %d processes.\n", proc_Num);
    for(int i = 0; i < proc_Num; i++) {
        
        children[i] = fork();
        if(children[i] == 0) {
            work();
        }
        else if(children[i] < 0) {
            perror("Process Creation unsuccessful. EXIT FAILURE\n");
            exit(EXIT_FAILURE);
        }
        usleep(500);
    }
    print();
    wait_prompt();
}

//------------------------------------------------------
// updateCount
//
// PURPOSE: Re-reads config file and decide whether to call increase() decrease()
//     or do nothing at all and prompt the user nothing was done. 
//     Lastly it prints the list of processes after completion and prints the Parent PID
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
    else if(difference < 0){
        difference = count - temp;
        printf("decreasing processes by %d\n", difference);
        decrease(difference);
    }
    else {

        printf("There are already this many processes.\n");  
    } 
    print();
    wait_prompt();
}

//------------------------------------------------------
// increase
//
// PURPOSE: Reallocates worker array and increase number of current workers by n (nums) 
// and sends them to be configured for work.
// INPUT PARAMETERS:
//     int nums - represents the number of processes we need to create
// OUTPUT PARAMETERS:
//     None
// REMARKS: This is different from create because we must
//     realloc memory and nums represents how many more
//     processes we need to create.
//------------------------------------------------------
void increase(int nums) {

    // we need to realloc to increase size
    children = realloc(children, (nums+count+1) * sizeof(pid_t));
    
    // start at newest index
    printf("Creating %d processes.\n", nums);
    for(int i = count; i < count + nums; i++) {
        
        children[i] = fork();
        if(children[i] == 0) {
            work();
        }
        else if(children[i] < 0) {
            perror("Process Creation unsuccessful. EXIT\n");
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
//     int nums - represents the number of processes we need to remove
// OUTPUT PARAMETERS:
//     None
//------------------------------------------------------
void decrease(int nums) {
    int lower_bound = count-nums;
    printf("Removing %d processes\n", nums);
    
    if(lower_bound > -1) {
        for(int i = count-1; i > lower_bound-1; i--) {
            
            // Kill Slowly
            printf("Killing CHILD process [ID: %d]\n", children[i]);
            kill(children[i],SIGUSR2);
            usleep(10000);
            count--;       
        }     
    }
    
    // realloc to decrease size but ensure there is always one space for safety
    children = realloc(children, ((count)+1));
    
    // no processes means we are free to exit
    if(count == 0) {
        free(children);
    } 
}

//------------------------------------------------------
// work
//
// PURPOSE: Configures processes to the appropriate signals
//     and runs them indefinitely until given permission by the main process
//     to exit.
// INPUT PARAMETERS:
//     None
// OUTPUT PARAMETERS:
//     None
//------------------------------------------------------
void work() {

    // signal handlers for child processes
    signal(SIGUSR2, sigusr2_handler);
    signal(SIGINT, SIG_IGN);
    printf("Child Process [ID: %d] started!\n", getpid());
    
    // (work)
    while(1) {
        sleep(1);
    }
}


//------------------------------------------------------
// sighup_handler
//
// PURPOSE: Handles SIGHUP signal and updates the number of processes
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
// PURPOSE: handles SIGUSR2 signal which corresponds to communication
//    of the parent telling a particular child process to exit
// INPUT PARAMETERS:
//     None
// OUTPUT PARAMETERS:
//     None
//------------------------------------------------------
void sigusr2_handler() {
    printf("Child Process [ID: %d] killed\n", getpid());
    usleep(10000);
    exit(EXIT_SUCCESS);
}

//------------------------------------------------------
// sigint_handler
//
// PURPOSE: When SIGINT is received kills all processes
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
// killall()   
//
// PURPOSE: Sends all processes to be killed
// INPUT PARAMETERS:
//     None:
// OUTPUT PARAMETERS:
//     None
//------------------------------------------------------
void killAll() {
        // kill all processes in list
        assert(count > 0);
        printf("We are going to close all processes now!\n");
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

        printf("Child Process [ID: %d]\n", children[i]);
    }
    printf("---------------------------\n\n");
}
