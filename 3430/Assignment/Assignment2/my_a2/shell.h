#ifndef _SHELL_H
#define _SHELL_H
#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <assert.h>

void openFile(FILE** file, char fileName[]);
void parse_File(FILE** file);
void process_Line(char *line);
void execute_Commands(char **tokens, int position);
void redirect(char *redirect, char *filename);
void execute_Pipe(char **args, char **tokens, int curr, int end);
void parse_Commands(char ** args, char **tokens, int start , int end);
void execute_Sub(char** args, char ** tokens, int curr, int end);
void format_Array(char** args, int start, int end);
#endif

