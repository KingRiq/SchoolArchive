//-----------------------------------------
// NAME: Eriq Hampton 
// STUDENT NUMBER: 7852830
// COURSE: COMP 3430, SECTION: A01
// INSTRUCTOR: Robert Guderian
// LAB 2
// 
// REMARKS: Create n child processes to run arguments passed as commands
// using execvp
//
//-----------------------------------------

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#include <ctype.h>

#define READ_END 0
#define WRITE_END 1
#define PIPE_LENGTH 2
#define MAX_LENGTH 100

void parse_Args(char* argv, char** arguments);
void close_Pipes(int process_length, int end, int pipe_fds[process_length][PIPE_LENGTH]);
int process_length;

int main(int argc, char* argv[]) {
    
    char buffer[4096];
    int proc_NUM = argc-1;              
    process_length = proc_NUM +1;
    pid_t children[process_length];
    int pipe_Array[process_length][PIPE_LENGTH];
    
    // argc <= 1 is invalid
    if(argc < 2) {
        printf("octopipe needs more than one argument\n");
        printf("USAGE -> ./octopipe \"argument2\" \"argument3\"\n");
        exit(EXIT_FAILURE);
    }
    
    // ignore [0] because that is a pipe to itself
    for(int i = 1; i < process_length; i++) {
        pipe(pipe_Array[i]);
    }

    // n = argc, create n-1 children
    for(int i = 1; i < process_length; i++) {

        // start at 1 so its not confusing (i-1, i+1, etc)
        // we are talking about the ith child and the ith argument not i+1
        printf("%d is about to start %s\n", getpid(), argv[i]);
        children[i] = fork();

        // child process
        if(children[i] == 0) {

            // DUP STDIN and close unnecessary file descriptors
            dup2(pipe_Array[i][0], STDIN_FILENO);
            close_Pipes(process_length, READ_END, pipe_Array);
            close_Pipes(process_length, WRITE_END, pipe_Array);
        
            char *arguments[MAX_LENGTH];
            parse_Args(argv[i], arguments);

            
            // heap allocations will be freed by execvp
            if(execvp(arguments[0], arguments) < 0) {
                printf("EXECVP did not execute successfully. Child Process [ID: %d] EXITING\n", getpid());
                exit(1);
            }
        }
        if(children[i] < 0) {
            printf("Child Process Creation Failed");
            exit(EXIT_FAILURE);
        }
        
    }
    
    // close all read ends for writing in parent
    close_Pipes(process_length, READ_END, pipe_Array);
    
    // read stdin and write to all children
    while (1){
        int count = read(STDIN_FILENO, buffer, sizeof(buffer));
        if (count == -1) {
            printf("READ ERROR\n");
            exit(EXIT_FAILURE); 
        } 
        else if (count == 0) {
            break;
        }
        else {
            
            // write to every child
            for(int i = 1; i < process_length; i++) {
                write(pipe_Array[i][1], &buffer[0], count);   
            }   
        }
    }

    // close all write ends
    close_Pipes(process_length, WRITE_END, pipe_Array);
    
    // wait for children
    while(wait(NULL)> 0);
    
    printf("Process Complete Parent [ID: %d] Terminating\n", getpid());
    exit(EXIT_SUCCESS);
}

void parse_Args(char* argv , char **arguments) {

    // no need to free memory exec does this for us
    char* line = strdup(argv);
    char* cmd;
    int length = 0;
    
    // tokenize
    cmd = strtok(line, " \n");
    while(cmd != NULL) {
        arguments[length] = cmd;
        cmd = strtok(NULL, " \n");
        length++;
    }
    arguments[length] = NULL;
}

// close all ends of the pipe we specify
void close_Pipes(int process_length, int end, int pipe_fds[process_length][PIPE_LENGTH]) {
    
    if(end == READ_END) {
        for(int i = 1; i < process_length; i++) {
            close(pipe_fds[i][READ_END]);
        }
    }
    
    if(end == WRITE_END) {
        for(int i = 1; i < process_length; i++) {
            close(pipe_fds[i][WRITE_END]);
        }
    }
}
