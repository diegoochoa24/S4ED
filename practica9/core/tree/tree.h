#ifndef _TREE_H
#define _TREE_H

#include <stdio.h>
#include <stdlib.h>


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
    int num_nodes;
} Tree;


//Function prototypes


#endif