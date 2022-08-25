#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/types.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include "shell.h"
#define BUFFER_SIZE 500

char ** task = NULL
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
    //execute_Commands(tokens, position);

    // clean up for each line
    printf("Command Complete\n\n");
    free(token);
    free(tokens);
}