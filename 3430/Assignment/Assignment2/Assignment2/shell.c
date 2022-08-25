//-----------------------------------------
// NAME: Eriq Hampton
// STUDENT NUMBER: 7852830
// COURSE: COMP 3430, SECTION: A01
// INSTRUCTOR: Robert Guderian
// ASSIGNMENT: Assignment 2, QUESTION: 1
//
// REMARKS: A simple Shell program in C
//
//-----------------------------------------
#include "shell.h"

#define BUFFER_SIZE 500
#define WRITE_END 1
#define READ_END 0

int main(int argc, char *argv[]){
    FILE *file;

    if(argc <= 1) {
        printf("Please enter an additional argument\n");
    }
    else {
        openFile(&file , argv[1]);
    }

    printf("Process Complete!\n");
    exit(EXIT_SUCCESS);
}

//------------------------------------------------------
// openFile
//
// PURPOSE: opens the script file
// INPUT PARAMETERS:
//     Takes a FILE and argument pointer to open the file and begin parsing
//      its contents line by line
// OUTPUT PARAMETERS:
//     None
//------------------------------------------------------
void openFile(FILE** file, char *arg){

    if((*file = fopen(arg, "r"))!= NULL) {
        printf("Successfully opened.\nfilename: %s\n\n", arg);
        parse_File(file);
    }
    else {
        printf("File couldn't be opened. Please try again!\n");
        exit(EXIT_FAILURE);
    }
}

//------------------------------------------------------
// parse_File
//
// PURPOSE: Upon successful read operation it begins to parse the script
//    file. It also passes the next line to parse to another method
// INPUT PARAMETERS:
//     File only.
// OUTPUT PARAMETERS:
//     None
//------------------------------------------------------
void parse_File(FILE **file) {
    assert(file != NULL);
    char *line;
    size_t buffer = 0;
    ssize_t line_buffer_size;
    line_buffer_size = getline(&line, &buffer, *file);

    while(line_buffer_size > 0) {
        process_Line(line);
        line_buffer_size = getline(&line, &buffer, *file);
    }

    // close the file
    free(line);
    line = NULL;
    fclose(*file);
}

//------------------------------------------------------
// process_Line
//
// PURPOSE: Used to tokenize the current line into executeable pieces
// INPUT PARAMETERS:
//     char *line;
// OUTPUT PARAMETERS:
//     None
//------------------------------------------------------
void process_Line(char *line) {

    
    char *token;
    char **tokens = malloc(BUFFER_SIZE * sizeof(char));
    int position = 0;

    printf("Processing Command: \n%s\n", line);

    // tokenize the line
    token = strtok(line, " \n");
    while(token != NULL) {
        tokens[position] = token;
        position++;
        token = strtok(NULL, " \n");
    }

    tokens[position] = NULL;
    execute_Commands(tokens, position);

    // clean up for each line
    printf("Command Complete\n\n");
    free(token);
    free(tokens);
}

//------------------------------------------------------
// execute_Command
//
// PURPOSE: Executes commands on the user's behalf
// INPUT PARAMETERS:
//     Forks a child process that will run the rest of the command
//      on that respective line. Parent waits until the child 
//      is finished with the command before proceeding.
// OUTPUT PARAMETERS:
//     None
//------------------------------------------------------
void execute_Commands(char **tokens, int position){

    pid_t pid = fork();
    
    if(pid < 0) {
        perror("Fork Failed\n");
        exit(EXIT_FAILURE);
    }
    else if(pid == 0) {
        char* args[position];
        parse_Commands(args, tokens, 0, position);
    }
    else {
        // parent process waits until entire command is complete before moving on to the next line
        while(wait(NULL)> 0);
    }
}

//------------------------------------------------------
// redirect
//
// PURPOSE: Redirection handler
// INPUT PARAMETERS:
//     takes the redirect symbol and the next position which should be a file
// OUTPUT PARAMETERS:
//     None
//------------------------------------------------------
void redirect(char *redirect, char *filename) {
    int in_fd;
    int out_fd;

    if(!strcmp(redirect, ">")) {
        if((out_fd = open(filename, O_CREAT | O_RDWR | O_APPEND, S_IRUSR | S_IWUSR)) < 0) {
            perror("Error opening file\n");
            exit(EXIT_FAILURE);
        }
        if(dup2(out_fd, STDOUT_FILENO) < 0) {
            perror("Output Redirection Dup Failure\n");
            exit(EXIT_FAILURE);
        }
        close(out_fd);
    }
    else {
        if((in_fd = open(filename, O_RDONLY)) < 0) {
            perror("Error opening file\n");
            exit(EXIT_FAILURE);
        }
        if(dup2(in_fd, STDIN_FILENO) < 0) {
            perror("Input Redirection Dup Failure\n");
            exit(EXIT_FAILURE);
        }
        close(in_fd);
    }  
}

//------------------------------------------------------
// execute_Pipe
//
// PURPOSE: executes a pipe operation. If the file is not
//  done executing commands it will pass the work back for additional parsing
// INPUT PARAMETERS:
//     char arg is the argument of the 1st command, tokens is the tokenized line
//     and 2 ints that represent where we are within the command
// OUTPUT PARAMETERS:
//     None
//------------------------------------------------------
void execute_Pipe(char **args ,char **tokens, int curr, int end) {
    
    pid_t pid;
    int fd[2];
    pipe(fd);
    char *args2[end];

    // advance curr past | character
    curr++;
    
    // Child for other side of pipe
    pid = fork();
    if(pid < 0) {
        perror("Fork Failed\n");
        exit(EXIT_FAILURE);
    }
    else if(pid == 0) {

        close(fd[WRITE_END]);

        if(dup2(fd[READ_END],STDIN_FILENO) < 0 ) {
            perror("Child pipe failure\n");
            exit(EXIT_FAILURE);
        }
        close(fd[READ_END]);
        parse_Commands(args2, tokens, curr, end);
    }
    
    // Parent (Format the array, setup pipe and exec)
    format_Array(args, curr, end);
    close(fd[READ_END]);

    if(dup2(fd[WRITE_END],STDOUT_FILENO) < 0) {
        perror("Parent Pipe failure\n");
        exit(EXIT_FAILURE);
    }
    close(fd[WRITE_END]);
    
    if(execvp(args[0], args) <0) {
        perror("Could not execute command\n");
        exit(EXIT_FAILURE);
    }          
}

//------------------------------------------------------
// parse_Commands
//
// PURPOSE: executes the commands it can 
// INPUT PARAMETERS:
//     Takes the argument line, list of tokens, and 2 ints 
//      which represent our current place and the end point
// OUTPUT PARAMETERS:
//     None
//------------------------------------------------------
void parse_Commands(char ** args, char **tokens, int curr , int end) {
    
    for(int i = curr; i < end; i++) {
            
        if((!strcmp(tokens[i], ">")|| !strcmp(tokens[i], "<"))) {
                
            redirect(tokens[i], tokens[i+1]);
            args[i-curr] = NULL;   
        }
        else {
            if(!strcmp(tokens[i], "|")) {
                execute_Pipe(args, tokens,i, end);
            }
            else if(strstr(tokens[i], "<(") != NULL) {

                args[i-curr] = NULL;
                execute_Sub(args, tokens, i, end); 
            }
            // set null after each token
            args[i-curr]= strdup(tokens[i]);
            args[i-curr+1]= NULL;
        }
    }
    
    assert(curr <= end);
    if((execvp(args[0], args)) < 0) {
        perror("Could not execute command\n");
        exit(EXIT_FAILURE);
    }
}

//------------------------------------------------------
// execute_Sub
//
// PURPOSE: Input Process Substitution Handler
// INPUT PARAMETERS:
//     Performs input process Substitution using
//      parse args into one command and progresses the current position closer to the end
// OUTPUT PARAMETERS:
//     None
//------------------------------------------------------
void execute_Sub(char** args, char ** tokens, int curr, int end) {
    
    pid_t pid;
    int fd;
    char * pipe = "pipe";
    char *args2[end];
    int start = curr;
    
    mkfifo(pipe, 0666);

    // remove "<(" from first token"
    args2[0] = strdup(tokens[curr]);
    memmove(args2[0], args2[0]+2, strlen(args2[0]));
    curr++;

    // parse the inner tokens into argument array
    while(strstr(tokens[curr],")") == NULL) {
        args2[curr-start] = strdup(tokens[curr]);
        curr++;
    }
    
    // remove ")" from final part of the argument and add null after it
    args2[curr-start] = strdup(tokens[curr]);
    args2[curr-start][strlen(args2[curr-start])-1] = '\0';
    args2[curr-start+1] = NULL;
    
    // fork so child knows what happened
    pid = fork();
    if(pid < 0) {
        perror("Fork Failed\n");
        exit(EXIT_FAILURE);
    }
    else if(pid == 0) {
       
        // Open FIFO for read
        fd = open(pipe, O_WRONLY);

        if(dup2(fd, STDOUT_FILENO) < 0) {
            perror("Child Process Substitution Dup Failure\n");
            exit(EXIT_FAILURE);
        }
        close(fd);

        format_Array(args2, curr-start+1, end);
        if(execvp(args2[0], args2) < 0) {
            perror("Child Process Substitution EXEC FAILURE\n");
            exit(EXIT_FAILURE);
        }

    }
    
    // Open FIFO for write only
    fd = open(pipe, O_RDONLY);  
    if(dup2(fd, STDIN_FILENO) < 0) {
        perror("Parent Process Substitution Dup Failure\n");
        exit(EXIT_FAILURE);
    }

    close(fd);
    unlink(pipe);

    // format array and continue
    curr++;
    format_Array(args, curr, end);
    parse_Commands(args, tokens, curr, end);   
}

//------------------------------------------------------
// format_Array
//
// PURPOSE: Add null
// INPUT PARAMETERS:
//     char args, int start which indicates where to begin, int end 
//      represents where to end
// OUTPUT PARAMETERS:
//     None
//------------------------------------------------------
void format_Array(char** args, int start, int end) {
    for(int i = start; i < end; i++) {
            args[i] = NULL;
    }
}
