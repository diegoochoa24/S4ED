#include <stdio.h>
#include <stdlib.h>
#include "../../app/components.h"
#include "queue.h"

void initialize_queue(Queue *queue){
    queue->front = NULL;
    queue->rear = NULL;
    queue->num_nodes = 0;
}

QueueNode *create_queue_node(){
    QueueNode *new_node = (QueueNode*)calloc(1, sizeof(QueueNode));
    cast_queue_data(new_node);

    if (!capture_queue_data(new_node->data)){
        free(new_node);
        ERROR(MEMORY_ALLOCATION);
        return NULL;
    }

    new_node->next = NULL;
    
    return new_node;
}

void enqueue(Queue *queue, QueueNode *new_node){
    if (queue->num_nodes == 0)
        queue->front = new_node;

    if (queue->rear != NULL)
        queue->rear->next = new_node;

    queue->rear = new_node;    
    new_node->next = NULL; 
    queue->num_nodes++; 
}

QueueNode *dequeue(Queue *queue){
    QueueNode *aux;
    aux = queue->front;
    if (queue->front->next != NULL){
        queue->front = queue->front->next;
        queue->num_nodes--;
    } else {
        initialize_queue(queue);
    }
    aux->next = NULL;
    return aux;
}

void print_queue(Queue *queue, int *index){
    if (queue->front == NULL){
        INFO(NO_FILES_ADDED);
        return;
    }

    int aux_num = 0;
    if (index == NULL)
        index = &aux_num;
    
    for(int i = 0; i < queue->num_nodes; i++){   
        print_queue_data(queue->front->data, index);
        enqueue(queue, dequeue(queue));
    }
    printf("\n");
}
