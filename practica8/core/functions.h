#ifndef _FUNCTIONS_H
#define _FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include "structs.h"

//file.c functions
void capture_file_data(File *file);
File *find_file (Mqueue *mqueue, int op);
void delete_file(Mqueue *mqueue, File *file);
void delete_all_files(Mqueue *mqueue, int running);
void process_file(Mqueue *mqueue);

//queue.c functions
void initialize_queue(Queue *queue);
Node *create_node();
void enqueue(Queue *queue, Node *new_node);
Node *dequeue(Queue *queue);
void add_node(Mqueue *mqueue, Node *node);
void print_queue(Queue *queue, int *num_file);

//mqueue.c functions
void initialize_mqueue(Mqueue *mqueue);
void menqueue(Mqueue *mqueue, Queue *new_queue);
Queue *mdequeue(Mqueue *mqueue);
void print_mqueue(Mqueue *mqueue);
void sort_mqueue(Mqueue *mqueue);

//priority.c functions
int compare_m2M(int m, int M);
int compare_M2m(int m, int M);
void set_priority(Mqueue *mqueue);

#endif