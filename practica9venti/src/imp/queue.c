


#include "structs.h"

Queue* createQueue() {
    Queue *queue = (Queue*)malloc(sizeof(Queue));
    queue->front = queue->rear = NULL;
    queue->num_nodes = 0;
    return queue;
}

void enqueue(Queue *queue, File *file) {
    QueueNode *node = (QueueNode*)malloc(sizeof(QueueNode));
    node->file = file;
    node->data_size = sizeof(File);
    node->next = NULL;
    if (queue->rear == NULL) {
        queue->front = queue->rear = node;
    } else {
        queue->rear->next = node;
        queue->rear = node;
    }
    queue->num_nodes++;
}

File* dequeue(Queue *queue) {
    if (queue->front == NULL)
        return NULL;

    QueueNode *temp = queue->front;
    File *file = temp->file;
    queue->front = queue->front->next;

    if (queue->front == NULL)
        queue->rear = NULL;

    free(temp);
    queue->num_nodes--;
    return file;
}
