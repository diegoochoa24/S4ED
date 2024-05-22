#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../file/file.h"
#include "queue.h"
#include "../util/const.h"


int capture_data(QueueNode *node){
    if (node == NULL){
        printf("\n\rNo valido...");
        return FALSE;
    }

    node->data = (File*)calloc(1, sizeof(File));
    if(capture_file_data(node->data)){
        return TRUE;
    } else {
        free(node->data);
        return FALSE;
    }
}

void print_data(QueueNode *node, int *index){
    if (node == NULL){
        printf("\n\rNo valido...");
        return FALSE;
    }

    if(print_file_data(node->data, index)){
        (*index)++;
        return TRUE;
    } else {
        free(node->data);
        return FALSE;
    }
}

void initialize_queue(Queue *queue){
    queue->front = NULL;
    queue->rear = NULL;
    queue->num_nodes = 0;
}

QueueNode *create_node(){
    QueueNode *new_node = (QueueNode*)calloc(1, sizeof(QueueNode));
    
    if (!capture_data(&new_node)){
        free(new_node);
        printf("\n\rNo se pudo capturar la informacion...");
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
        printf("\n\rNo hay archivos...");
        return;
    }

    int aux_num = 0;

    if (index == NULL)
        index = &aux_num;
    
    for(int i = 0; i < queue->num_nodes; i++){   
        print_data(queue->front, *index);
        enqueue(queue, dequeue(queue));
    }

    printf("\n");
}