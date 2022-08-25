#ifndef _PROCESSLINE_H
#define _PROCESSLINE_H
#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/queue.h> // queue taken from FreeBSD 10
#include <stdbool.h>
#include <time.h>
#include <errno.h>
#include <pthread.h>
#include <assert.h>

void openFile(FILE **file, char fileName[]);
void parse_File(FILE **file);
void process_Line(char *line);
#endif
