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

#include "../file/file.h"
//Queue prototypes
void initialize_queue(Queue *queue);
QueueNode *create_queue_node();
void enqueue(Queue *queue, QueueNode *new_node);
QueueNode *dequeue(Queue *queue);
void print_queue(Queue *queue, int *index);

//Queue data prototypes
void cast_queue_data(QueueNode *node);
int capture_queue_data(File *file);
void print_queue_data(File *file, int *index);

#endif
