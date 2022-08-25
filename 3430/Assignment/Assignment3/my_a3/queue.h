#ifndef _QUEUE_H
#define _QUEUE_H
#pragma once

#define BUFFER_SIZE 500
#define TIME_ALLOTMENT 200

typedef struct TaskQueue
{
    struct TNode *front, *rear;
    pthread_mutex_t queue_Lock;
    int nodeCount;
} Queue;

typedef struct TNode
{
    char *taskName;
    int taskType;
    int taskLength;
    int ioChance;
    int timeElasped;
    int timeLeft;
    int queueNum;
    struct timespec arrival; // time scheduled
    struct timespec start;   // time first run
    struct timespec end;     // time put into doneQueue queue
    struct TNode *next;
} task;

// create a new node for task
struct TNode *newNode1(char **tokens)
{

    struct TNode *temp = (struct TNode *)malloc(sizeof(struct TNode));
    temp->taskName = strdup(tokens[0]);
    temp->taskType = atoi(tokens[1]);
    temp->taskLength = atoi(tokens[2]);
    temp->ioChance = atoi(tokens[3]);
    temp->timeLeft = TIME_ALLOTMENT;
    temp->queueNum = 0;
    temp->timeElasped = 0;
    return temp;
}

// A utility function to create an empty queue
struct TaskQueue *createQueue()
{
    Queue *queue = (Queue *)malloc(sizeof(struct TaskQueue));
    queue->front = queue->rear = NULL;
    pthread_mutex_init(&(queue->queue_Lock), NULL);
    queue->nodeCount = 0;
    return queue;
}
void getLock(struct TaskQueue *q);
void giveLock(struct TaskQueue *q);

// The function to add a key k to queue
void enQueue(struct TaskQueue *queue, task *task)
{
    // Create a new LL node
    struct TNode *temp = task;
    queue->nodeCount++;

    // If queue is empty, then new node is front and rear both
    if (queue->rear == NULL)
    {
        queue->front = queue->rear = temp;
        return;
    }
    // Add the new node at the end of queue and change rear
    queue->rear->next = temp;
    queue->rear = temp;
}

// Function to remove a key from given queue queue
struct TNode *deQueue(struct TaskQueue *queue)
{
    // If queue is empty, return NULL.
    if (!(queue->front == NULL && queue->nodeCount == 0))
    {
        // Store previous front and move front one node ahead
        struct TNode *temp = queue->front;

        queue->front = queue->front->next;

        // If front becomes NULL, then change rear also as NULL
        if (queue->front == NULL)
            queue->rear = NULL;

        queue->nodeCount--;
        temp->next = NULL;
        return temp;
    }
    else
    {
        printf("Queue is empty\n");
    }
    return NULL;
}

int isEmpty(struct TaskQueue *queue)
{
    if (queue->front == NULL && queue->rear == NULL)
    {
        return true;
    }
    return false;
}
void printTasks(Queue *q1)
{
    task *task = q1->front;
    while (task)
    {
        printf("Task = %s\n", task->taskName);
        task = task->next;
    }
}
struct TNode *peek(struct TaskQueue *queue)
{
    getLock(queue);

    // now we can read safely
    if (!(queue->front))
    {
        // we are free to unlock and move on
        giveLock(queue);
    }
    return queue->front;
}

void getLock(struct TaskQueue *q)
{

    pthread_mutex_lock(&q->queue_Lock);
}
void giveLock(struct TaskQueue *q)
{

    pthread_mutex_unlock(&q->queue_Lock);
}
#endif
