#ifndef _QUEUE_H
#define _QUEUE_H
#include <sys/queue.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#pragma pack(push)
#pragma pack(1)


typedef struct ClusterQueue
{
    struct CNode *front, *rear;
    int nodeCount;
} Queue;

typedef struct CNode
{
    uint32_t clusterNum;
    struct CNode *next;
} nodes;

int isEmpty(struct ClusterQueue *queue);
// create a new node for cluster
struct CNode *newNode(uint32_t clusterNum)
{

    struct CNode *temp = (struct CNode *)malloc(sizeof(struct CNode));
    temp->clusterNum = clusterNum;
    return temp;
}

// A utility function to create an empty queue
struct ClusterQueue *createQueue()
{
    Queue *queue = (Queue *)malloc(sizeof(struct ClusterQueue));
    queue->front = queue->rear = NULL;
    queue->nodeCount = 0;
    return queue;
}


// The function to add a key k to queue
void enQueue(struct ClusterQueue *queue, uint32_t value)
{
    // Create a new LL node
    struct CNode *temp;
    temp = (struct CNode *)malloc(sizeof(struct CNode));
    temp->clusterNum = value;
    temp->next = NULL;

    // If queue is empty, then new node is front and rear both
    if (queue->front == NULL && queue->rear == NULL)
    {
        queue->front = queue->rear = temp;
        queue->nodeCount++;
        return;
    }
    // Add the new node at the end of queue and change rear
    queue->rear->next = temp;
    queue->rear = temp;
    queue->nodeCount++;
    
}

// Function to remove a key from given queue queue
struct CNode *deQueue(struct ClusterQueue *queue)
{
    //printf("before node count = %d\n", queue->nodeCount);
    // If queue is empty, return NULL.
    if (queue->front != NULL)
    {
        // Store previous front and move front one node ahead
        struct CNode *temp = queue->front;

        queue->front = queue->front->next;
        
        // If front becomes NULL, then change rear also as NULL
        if (queue->front == NULL) {
            queue->rear = NULL;
            //queue->nodeCount = 0;
        }

        queue->nodeCount--;
        //printf("after node count = %d\n", queue->nodeCount);
        temp->next = NULL;
        return temp;
    }
    else
    {   
        //printf("empty = %d\n", isEmpty(queue));
        assert(queue->nodeCount == 0);
    }
    return NULL;
}

int isEmpty(struct ClusterQueue *queue)
{
    if (queue->front == NULL && queue->rear == NULL && queue->nodeCount==0)
    {
        return true;
    }
    return false;
}
void printTasks(Queue *queue)
{
    nodes *node = queue->front;
    while (node)
    {
        printf("Cluster = %u\n", node->clusterNum);
        node = node->next;
    }
}
struct CNode *peek(struct ClusterQueue *queue)
{
    return queue->front;
}


#pragma pack(pop)
#endif



