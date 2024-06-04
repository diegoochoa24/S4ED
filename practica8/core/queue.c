#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"
#include "functions.h"
#include "../util/const.h"


void initialize_queue(Queue *queue){
    queue->start = NULL;
    queue->end = NULL;
    queue->num_nodes = 0;
}

Node *create_node(){
    Node *new_node = (Node*)calloc(1, sizeof(Node));
    capture_file_data(&(new_node->file));

    if (new_node->file.filename == NULL || new_node->file.pages <= 0)
        return NULL;

    new_node->next = NULL;

    return new_node;
}

void enqueue(Queue *queue, Node *new_node){
    if (queue->num_nodes == 0)
        queue->start = new_node;

    if (queue->end != NULL)
        queue->end->next = new_node;

    queue->end = new_node;    
    new_node->next = NULL; 
    queue->num_nodes++; 
}

Node *dequeue(Queue *queue){
    Node *aux;
    aux = queue->start;
    if (queue->start->next != NULL){
        queue->start = queue->start->next;
        queue->num_nodes--;
    } else {
        initialize_queue(queue);
    }
    aux->next = NULL;
    return aux;
}

void add_node(Mqueue *mqueue, Node *node){
    
    Queue *queue_aux = NULL;

    for(int i = 0; i < mqueue->num_queues; i++){
        if (mqueue->start->start->file.pages == node->file.pages)
            queue_aux = mqueue->start;
        
        menqueue(mqueue, mdequeue(mqueue));
    }

    if (queue_aux != NULL){
        enqueue(queue_aux, node);
    } else {
        queue_aux = (Queue*)calloc(1, sizeof(Queue));
        initialize_queue(queue_aux);
        enqueue(queue_aux, node);
        menqueue(mqueue, queue_aux);
        sort_mqueue(mqueue);
        return;
    } 
}

void print_queue(Queue *queue, int *num_file){
    if (queue->start == NULL){
        printf("\n\rNo hay archivos...");
        return;
    }

    int aux_num = 0;

    if (num_file == NULL)
        num_file = &aux_num;
    
    for(int i = 0; i < queue->num_nodes; i++){   
        printf("\n\r[%d] - %s (%d)", *num_file, queue->start->file.filename, queue->start->file.pages);
        (*num_file)++;
        enqueue(queue, dequeue(queue));
    }
    printf("\n");
}