//-----------------------------------------
// NAME: Eriq Hampton 
// STUDENT NUMBER: 7852830
// COURSE: COMP 3430, SECTION: A01
// INSTRUCTOR: Robert Guderian
// LAB 1: Lab #1, QUESTION: question 2
// 
// REMARKS: Create n child processes and wait for a signal
// teaches signal handling.
//
//-----------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>


void check_Valid(int, char*[]);
void handle();
void handle2();
void handle3();

int volatile counter = 0;

int main(int argc, char* argv[]) {
    
    // check for valid arguments
    check_Valid(argc, argv);

    // n processes
    int proc_Num = atoi(argv[1]);
    
    // array of child processes
    pid_t children[proc_Num];

    
    printf("Hello I am the Parent [Process: %d]\n",getpid());
    printf("Creating %d processes...\n", proc_Num);

    // Parent signal handles
    signal(SIGUSR1,handle);
    signal(SIGUSR2, handle3);
    
    
    
    for(int i = 0; i < proc_Num;  i++) {
        children[i] = fork();

        // (child proccesses)
        if(children[i] == 0) {

            // print, send signal and sleep
            signal(SIGUSR2, handle2);
            printf("Process %d created\n", i+1);
            printf("Hello I am Child [Process %d] from Parent [Process pid] %d\n",getpid(),getppid());

            
            kill(getppid(),SIGUSR1); 
            while(1){
                sleep(1);           
            }   
        }
        // slow down creation
        usleep(500);
    }
     
    // (parent process) "wait" until every child has sent a signal
    while(counter != proc_Num);

    // signal every child and then itself.
    if(counter == proc_Num) {
       for(int i = 0; i< proc_Num; i++){
           kill(children[i], SIGUSR2); 
           
       }
       raise(SIGUSR2);         
    }


    printf("Parent [Process: %d] waiting for children\n", getpid());
    
    //wait until everyone is done
    while(wait(NULL) > 0); 
    printf("Process Complete. Parent [Process: %d] Terminating! \n", getpid());
    
    exit(0);
    
}

// There are 3 handlers 2 handlers for the Parent process(handle and handle3) and 1 for the children (handle2)
void handle() {
    counter++;
    printf("SIGUSR1 Signal Received! heard by Parent [Process: %d], Signals heard = %d\n", getpid(), counter);

}
void handle2(){
    printf("Child [Process: %d] heard SIGUSR2. Time to terminate!\n", getpid());

    // slow down
    sleep(1);
    exit(0);
}
void handle3() { 
    printf("Parent [Process: %d] heard SIGUSR2 but cannot exit the program\n" , getpid()); 
}

void check_Valid(int argc, char* argv[]) {
    if(argc != 2) {
        
        printf("please enter only 2 arugments\n");
        printf("%d\n", argc);

        exit(0);
    }

    // 0 or below as an argument means there is no work to do.
    if(atoi(argv[1]) < 1) {  
        printf("please enter a positive integer as an argument!\n");
        exit(0);
    }
}
