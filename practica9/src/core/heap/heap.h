#ifndef _HEAP_H
#define _HEAP_H

#include <stdio.h>
#include <stdlib.h>
#include "../tree/tree.h"


//Heap structures
typedef enum {
    MIN_HEAP,
    MAX_HEAP
} HeapType;

typedef struct HeapTree
{
    TreeNode *root;
    int num_nodes;
    HeapType type;
} HeapTree;

typedef struct HeapArray
{
    void **elements;
    size_t element_size;
    int size;
    HeapType type;
} HeapArray;

typedef struct Heap
{
    HeapTree *tree_form;
    HeapArray *array_form;
    int size;
    HeapType type;
} Heap;


//Function prototypes


#endif