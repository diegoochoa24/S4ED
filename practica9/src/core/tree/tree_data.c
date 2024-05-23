#include <stdio.h>
#include "../file/file.h"
#include "../tree/tree.h"

void cast_tree_data(TreeNode *node){
    node->data = (Queue*)calloc(1, sizeof(Queue));
    node->data_size = sizeof(Queue);
}

CompareTreeData compare_tree_data(TreeNode *actual, QueueNode *data){
    Queue *queue_actual = actual->data;
    File *file_actual = queue_actual->front->data;

    File *file_new_node = data->data;

    if (file_actual->pages == file_new_node->pages){
        return EQUAL;
    } else if (file_actual->pages > file_new_node->pages){
        return ACTUALFAVOR;
    } else {
        return DATAFAVOR;
    }
}

void insert_data_into_tree(TreeNode *actual, QueueNode *data){
    Queue *queue_actual = actual->data;
    enqueue(queue_actual, data);
}

void print_tree_data(TreeNode* node)
{
    Queue *dataTree = node->data;
    File *dataQueue = dataTree->front->data;

    printf("(%d)", dataQueue->pages);
}
