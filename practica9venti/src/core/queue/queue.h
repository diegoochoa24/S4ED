#ifndef QUEUE_H
#define QUEUE_H

#include <stdlib.h>

//Queue structures
typedef struct QueueNode
{
    void *data;
    size_t data_size;
    struct QueueNode *next;
} QueueNode;

typedef struct Queue
{
    QueueNode *front;
    QueueNode *rear;
    short int num_nodes;
} Queue;


#endif
