#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <errno.h>
#include "processLine.h"
#include <pthread.h>
#include <assert.h>
#include "timefunct.h"
#include "queue.h"

#define QUANTUM_LENGTH 50 // microseconds
#define TIME_ALLOTMENT 200
int taskCount = 0;
void priorityBoost();
void runTask();
bool firstDelay = true;
bool tasksAvailable = true;
struct timespec timeZero;
bool endofprogram = false;
pthread_mutex_t threadLock = PTHREAD_MUTEX_INITIALIZER;

int cpuNum = 0;
int timeSlice = 0;
bool notasksever = false;

// MLFQ
struct TaskQueue *q1 = NULL;
struct TaskQueue *q2 = NULL;
struct TaskQueue *q3 = NULL;

// DONE QUEUE
struct TaskQueue *doneQueue = NULL;
void printStats();

//------------------------------------------------------
// work
//
// PURPOSE: Simulate work for a task
// INPUT PARAMETERS:
//     None
// OUTPUT PARAMETERS:
//     None
//------------------------------------------------------
void *work(void *args)
{
    (void)args;

    // sleep indefinitely
    while (!endofprogram || !notasksever)
    {
        runTask();
    }

    // compiler requires this but never runs
    pthread_exit(EXIT_SUCCESS);
}

int getMin(int x, int y);
void lowerPriority(struct TNode *);
void schedule(struct TNode *);

struct TNode *peek(struct TaskQueue *q);
// Driver Program to test anove functions

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
void openFile(FILE **file, char *arg)
{

    if ((*file = fopen(arg, "r")) != NULL)
    {
        printf("Successfully opened.\nfilename: %s\n\n", arg);
        parse_File(file);
    }
    else
    {
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
void parse_File(FILE **file)
{
    // initialize timeZero
    clock_gettime(CLOCK_REALTIME, &timeZero);
    assert(file != NULL);
    char *line;
    size_t buffer = 0;
    ssize_t line_buffer_size;
    line_buffer_size = getline(&line, &buffer, *file);

    while (line_buffer_size > 0)
    {
        process_Line(line);
        line_buffer_size = getline(&line, &buffer, *file);
    }

    notasksever = true;
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
void process_Line(char *line)
{

    char *token;
    char **tokens = malloc(BUFFER_SIZE * sizeof(char));
    int position = 0;

    // tokenize the line
    token = strtok(line, " \n");
    while (token != NULL)
    {
        tokens[position] = token;
        position++;
        token = strtok(NULL, " \n");
    }

    tokens[position] = NULL;
    if (strcmp(tokens[0], "DELAY"))
    {

        task *newTask = newNode1(tokens);
        newTask->queueNum = 1;
        if (firstDelay == true)
        {
            // these are the first batch
            newTask->arrival = timeZero;
        }
        else
        {
            clock_gettime(CLOCK_REALTIME, &newTask->arrival);
        }
        schedule(newTask);
        taskCount++;
    }
    else
    {
        printf("Delay Detected\n");

        if (firstDelay == true)
        {
            // now we refer
            firstDelay = false;
        }

        milsleep(atoi(tokens[1]));
    }

    // clean up for each line
    free(token);
    free(tokens);
}

void priorityBoost()
{
    task *t = NULL;

    // if the queues are empty there is nothing boost
    if (!(isEmpty(q1) && isEmpty(q2) && isEmpty(q3)))
    {
        printf("Initiating Priority Boost\n");
        // boost empty q2,q3 and put it in q1
        while (q2->front)
        {
            t = deQueue(q2);
            t->timeLeft = TIME_ALLOTMENT;
            enQueue(q1, t);
        }
        while (q3->front)
        {
            t = deQueue(q3);
            t->timeLeft = TIME_ALLOTMENT;
            t->queueNum = 1;
            enQueue(q1, t);
        }
        printf("Priority BOOSTED!!!\n");
    }
}

void runTask()
{

    task *t = NULL;

    // if p(a) > p(b) = a
    if (peek(q1))
    {
        // get lock and grab task
        t = deQueue(q1);
        giveLock(q1);
    }
    else if (peek(q2))
    {
        t = deQueue(q2);
        giveLock(q2);
    }
    else if (peek(q3))
    {
        t = deQueue(q3);
        giveLock(q3);
    }

    if (t)
    {
        // mark the start time
        if (t->start.tv_sec == 0)
        {
            clock_gettime(CLOCK_REALTIME, &t->start);
        }

        // determine IO [0-100]
        int IOchance = rand() % 101;
        int num = 0;
        bool IO = false;
        if (t->ioChance >= IOchance)
        {
            // determine
            IO = true;
        }

        if (t->taskLength < QUANTUM_LENGTH)
        {
            microsleep(t->taskLength);

            // put it in doneQueue
            clock_gettime(CLOCK_REALTIME, &t->end);
            getLock(doneQueue);
            enQueue(doneQueue, t);
            giveLock(doneQueue);
        }
        if (t->timeLeft > 0)
        {
            // what is the minimum time we can run
            int timeRemaining = t->taskLength - t->timeElasped;

            int min = getMin(QUANTUM_LENGTH, t->timeLeft);
            min = getMin(min, timeRemaining);

            if (timeRemaining > 0)
            {
                if (IO == true)
                {
                    num = rand() % min + 1;

                    min = getMin(min, num); // for safety
                }

                if (min == QUANTUM_LENGTH)
                {
                    // run for QL amount of time
                    microsleep(QUANTUM_LENGTH);
                    t->timeElasped += QUANTUM_LENGTH;
                    t->timeLeft = t->timeLeft - QUANTUM_LENGTH;

                    // schedule
                    if (t->timeLeft > 0)
                    {
                        schedule(t);
                    }
                    else
                    {
                        lowerPriority(t);
                    }
                }
                else if (min == t->timeLeft)
                {
                    microsleep(t->timeLeft);
                    t->timeElasped += t->timeLeft;
                    t->timeLeft = 0;

                    lowerPriority(t);
                }
                else if (min == timeRemaining)
                {
                    microsleep(timeRemaining);
                    t->timeElasped += timeRemaining;

                    assert(t->timeElasped == t->taskLength);
                    clock_gettime(CLOCK_REALTIME, &t->end);
                    enQueue(doneQueue, t);
                }
                else if (min == num)
                {

                    microsleep(num);
                    t->timeElasped += num;
                    t->timeLeft -= num;

                    schedule(t);
                }
            }
            else
            {
                assert(t->timeElasped == t->taskLength);
                clock_gettime(CLOCK_REALTIME, &t->end);
                enQueue(doneQueue, t);
            }
        }
    }
}

int getMin(int x, int y)
{
    if (x > y)
    {
        return y;
    }
    return x;
}

void schedule(struct TNode *task)
{
    if (task->queueNum == 3)
    {
        getLock(q3);
        enQueue(q3, task);
        giveLock(q3);
    }
    else if (task->queueNum == 2)
    {
        getLock(q2);
        enQueue(q2, task);
        giveLock(q2);
    }
    else
    {
        assert(task->queueNum == 1);
        getLock(q1);
        enQueue(q1, task);
        giveLock(q1);
    }
}

// there is not priority lower than 3 so put it back in queue3
void lowerPriority(struct TNode *task)
{
    if (task->queueNum == 1)
    {
        task->queueNum++;
        task->timeLeft = TIME_ALLOTMENT;
        getLock(q2);
        enQueue(q2, task);
        giveLock(q2);
    }
    else if (task->queueNum == 2)
    {
        task->queueNum++;
        task->timeLeft = TIME_ALLOTMENT;
        getLock(q3);
        enQueue(q3, task);
        giveLock(q3);
    }
    else if (task->queueNum == 3)
    {
        task->timeLeft = TIME_ALLOTMENT; // q3 has no time allinement
        getLock(q3);
        enQueue(q3, task);
        giveLock(q3);
    }
}

void printStats()
{
    int type[4] = {0, 0, 0, 0};
    long responseTotal[4] = {0, 0, 0, 0};
    long turnaroundTotal[4] = {0, 0, 0, 0};
    long responseAVG[4] = {0, 0, 0, 0};
    long turnaroundAVG[4] = {0, 0, 0, 0};
    struct timespec temp1;
    struct timespec temp2;

    printf("Using mlfq with %d CPUs.\n", cpuNum);

    while (doneQueue->front)
    {
        // increment number of types
        type[doneQueue->front->taskType]++;

        // get the difference in times
        temp1 = diff(doneQueue->front->arrival, doneQueue->front->start);
        temp2 = diff(doneQueue->front->arrival, doneQueue->front->end);

        // calculate response time
        responseTotal[doneQueue->front->taskType] += temp1.tv_sec * USEC_PER_SEC;
        responseTotal[doneQueue->front->taskType] += temp1.tv_nsec / NANOS_PER_USEC;

        // calculate turnaround time
        turnaroundTotal[doneQueue->front->taskType] += temp2.tv_sec * USEC_PER_SEC;
        turnaroundTotal[doneQueue->front->taskType] += temp2.tv_nsec / NANOS_PER_USEC;
        free(deQueue(doneQueue));
    }

    for (int i = 0; i < 4; i++)
    {

        responseAVG[i] = responseTotal[i] / type[i];
        turnaroundAVG[i] = turnaroundTotal[i] / type[i];
    }

    printf("num of type Type 0 = %d\n", type[0]);
    printf("num of type Type 1 = %d\n", type[1]);
    printf("num of type Type 2 = %d\n", type[2]);
    printf("num of type Type 3 = %d\n", type[3]);

    // print Average Turnaround Time Log
    printf("Average turnaround time per type:\n");
    printf("Type 0 = %ld useconds\n", responseAVG[0]);
    printf("Type 1 = %ld useconds\n", responseAVG[1]);
    printf("Type 2 = %ld useconds\n", responseAVG[2]);
    printf("Type 3 = %ld useconds\n", responseAVG[3]);

    // print Response Time Log
    printf("Average response time per type:\n");
    printf("Type 0 = %ld useconds\n", responseAVG[0]);
    printf("Type 1 = %ld useconds\n", responseAVG[1]);
    printf("Type 2 = %ld useconds\n", responseAVG[2]);
    printf("Type 3 = %ld useconds\n", responseAVG[3]);
}

void *sThread(void *args)
{
    (void)args;

    while (!endofprogram)
    {
        printf("Sleeping for %d miliseconds\n", timeSlice);
        milsleep(timeSlice);

        // get all the locks
        getLock(q1);
        getLock(q2);
        getLock(q3);
        priorityBoost();
        giveLock(q1);
        giveLock(q2);
        giveLock(q3);
    }

    pthread_exit(EXIT_SUCCESS);
}

int main(int argc, char **argv)
{
    pthread_t sleep_thread;
    timeSlice = atoi(argv[2]);
    cpuNum = atoi(argv[1]);
    pthread_t workers[cpuNum];

    q1 = createQueue();
    q2 = createQueue();
    q3 = createQueue();
    doneQueue = createQueue();

    // create N threads
    for (int i = 0; i < cpuNum; i++)
    {
        if (pthread_create(&workers[i], NULL, &work, &i) != 0)
        {
            perror("Thread creation unsuccessful. EXIT\n");
            exit(EXIT_SUCCESS);
        }
    }

    // Start Priority Boost
    if (pthread_create(&sleep_thread, NULL, sThread, NULL) != 0)
    {
        perror("Thread creation unsuccessful. EXIT\n");
        exit(EXIT_SUCCESS);
    }

    // read tasks in line by line
    FILE *file;
    if (argc <= 1)
    {
        printf("Please enter an additional argument\n");
    }
    else
    {
        openFile(&file, argv[3]);
    }
    while (taskCount != doneQueue->nodeCount)
    {
        printf("taskCount %d\n", taskCount);
        printf("doneQueue  %d\n", doneQueue->nodeCount);
    }

    // clean up
    endofprogram = true;
    pthread_join(sleep_thread, NULL);
    for (int i = 0; i < cpuNum; i++)
    {
        pthread_join(workers[i], NULL);
    }
    printStats();
    free(q1);
    free(q2);
    free(q3);
    free(doneQueue);

    printf("Process Complete\n");
    return EXIT_SUCCESS;
}
