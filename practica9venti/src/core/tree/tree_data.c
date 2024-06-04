#include <stdio.h>
#include "../file/file.h"
#include "tree.h"

void cast_tree_data(TreeNode *node){
    node->data = (Queue*)calloc(1, sizeof(Queue));
    node->data_size = sizeof(Queue);
}

void insert_data_into_tree(TreeNode *actual, QueueNode *data){
    Queue *queue_actual = actual->data;
    enqueue(queue_actual, data);
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

CompareTreeData compare_tree_node(TreeNode *actual, TreeNode *new_node){
    Queue *queue_actual = actual->data;
    File *file_actual = queue_actual->front->data;

    Queue *queue_new_node = new_node->data;
    File *file_new_node = queue_new_node->front->data;

    if (file_actual->pages == file_new_node->pages){
        return EQUAL;
    } else if (file_actual->pages > file_new_node->pages){
        return ACTUALFAVOR;
    } else {
        return DATAFAVOR;
    }
}

void print_tree_data(TreeNode* node)
{
    Queue *dataTree = (Queue *)node->data;
    File *dataQueue = (File *)dataTree->front->data;

    printf("(%d)", dataQueue->pages);
}
