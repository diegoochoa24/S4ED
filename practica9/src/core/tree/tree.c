#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

void initialize_tree(Tree *tree){
    tree->root = NULL;
    tree->num_nodes = 0;
}

TreeNode *create_tree_node(void *data){
    TreeNode *node = (TreeNode*)calloc(1, sizeof(TreeNode));
    cast_tree_data(node);
    node->left = NULL;
    node->right = NULL;
    return node;
}

void insert_tree_data(Tree *tree, TreeNode **node, void *data){
    if (*node == NULL){
        *node = create_tree_node(data);
        insert_data_into_tree(*node, data);
        tree->num_nodes++;
        return;
    }

    if (compare_tree_data(*node, data) == EQUAL)
        insert_data_into_tree(*node, data);


    if (compare_tree_data(*node, data) == ACTUALFAVOR){
        insert_tree_data(tree, &((*node)->left), data);
    } else {
        insert_tree_data(tree, &((*node)->right), data);
    }
}

void print_tree(TreeNode* node, int level)
{
    int i;
    if (node != NULL)
    {
        print_tree_data(node);
        if(node->right!=NULL)
        {
            printf("\n");
            for (i = 0; i < level+1; i++)
            {
                if(i==level)
                    printf(" |____R ");
                else
                    printf(" |      ");
            }
            print_tree(node->right, level + 1);
        }
        if(node->left!=NULL)
        {
            printf("\n");
            for (i = 0; i < level+1; i++)
            {
                printf(" |      ");
            }
            printf("\n");
            for (i = 0; i < level+1; i++)
            {
                if(i==level)
                    printf(" |____L ");
                else
                    printf(" |      ");
            }
            print_tree(node->left, level + 1);
        }
    }
}
