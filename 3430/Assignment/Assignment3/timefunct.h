#ifndef _TIMEFUNCT_H
#define _TIMEFUNCT_H
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
#define NANOS_PER_USEC 1000
#define USEC_PER_SEC 1000000

struct timespec diff(struct timespec start, struct timespec end);
static void microsleep(unsigned int usecs);
int milsleep(int msec);

struct timespec diff(struct timespec start, struct timespec end)
{
    struct timespec temp;
    if ((end.tv_nsec - start.tv_nsec) < 0)
    {
        temp.tv_sec = end.tv_sec - start.tv_sec - 1;
        temp.tv_nsec = 1000000000 + end.tv_nsec - start.tv_nsec;
    }
    else
    {
        temp.tv_sec = end.tv_sec - start.tv_sec;
        temp.tv_nsec = end.tv_nsec - start.tv_nsec;
    }
    return temp;
}
static void microsleep(unsigned int usecs)
{
    long seconds = usecs / USEC_PER_SEC;
    long nanos = (usecs % USEC_PER_SEC) * NANOS_PER_USEC;
    struct timespec t = {.tv_sec = seconds, .tv_nsec = nanos};
    int ret;

    do
    {
        ret = nanosleep(&t, &t);
        // need to loop, `nanosleep` might return before sleeping
        // for the complete time (see `man nanosleep` for details)
    } while (ret == -1 && (t.tv_sec || t.tv_nsec));
}

int milsleep(int msec)
{
    printf("%d\n", msec);
    struct timespec ts;
    int res;

    ts.tv_sec = msec / 1000;
    ts.tv_nsec = (msec % 1000) * 1000000;

    do
    {
        res = nanosleep(&ts, &ts);
    } while (res && errno == EINTR);

    return res;
}
#endif
