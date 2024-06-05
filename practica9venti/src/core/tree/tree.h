#ifndef TREE_H
#define TREE_H

#include <stdio.h>
#include <stdlib.h>
#include "../queue/queue.h"

//Tree structures
typedef struct TreeNode
{
    void *data;
    size_t data_size;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

typedef struct Tree
{
    TreeNode *root;
    int level;
    int num_nodes;
} Tree;

typedef enum {
    EQUAL,
    ACTUALFAVOR,
    DATAFAVOR
} CompareTreeData;


//Tree prototypes
void initialize_tree(Tree *tree);
TreeNode *create_tree_node();
void insert_tree_data(Tree *tree, TreeNode **node, void *data);
void print_tree(TreeNode* node, int level);

//Tree data prototypes
void cast_tree_data(TreeNode *node);
void insert_data_into_tree(TreeNode *actual, QueueNode *data);
CompareTreeData compare_tree_data(TreeNode *actual, QueueNode *data);
CompareTreeData compare_tree_node(TreeNode *actual, TreeNode *new_node);
void print_tree_data(TreeNode* node);

#endif