#ifndef _QUEUES_H
#define _QUEUES_H

#include <stdio.h>
#include <stdlib.h>

typedef struct file
{
    char *filename;
    short int pages;
} File;

typedef struct node
{
    File file;
    struct node *next;
} Node;

typedef struct queue
{
    Node *start;
    Node *end;
    short int num_nodes;
    struct queue *next;
} Queue;

typedef int (*compare)(int m, int M);

typedef struct mqueue
{
    Queue *start;
    Queue *end;
    short int num_queues;
    short int priority;
    compare compare;
} Mqueue;

#endif
