#ifndef HEAP_H
#define HEAP_H

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
    Tree *tree;
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

//Heap prototypes
void initialize_heap(Heap *heap);
void add_node(Heap *heap);
void set_heap_type(Heap *heap, HeapType type);
void print_heap(Heap *heap);

//Priority prototypes
//int compare_m2M(int m, int M);
//int compare_M2m(int m, int M);
//void set_priority(Mqueue *mqueue);

#endif