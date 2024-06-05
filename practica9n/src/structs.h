#ifndef STRUCTS_H
#define STRUCTS_H

//Structs
typedef struct File {
    char *filename;
    short int pages;
} File;

typedef struct Node {
    File *file;
    struct Node *left;
    struct Node *right;
} Node;

typedef enum {
    MIN_HEAP,
    MAX_HEAP
} HeapType;

typedef struct HeapTree {
    Node *root;
    int level;
    int num_nodes;
    HeapType type;
} HeapTree;

typedef struct HeapArray {
    Node **elements;
    int size;
    int capacity;
    HeapType type;
} HeapArray;

typedef struct Heap {
    HeapTree *tree_form;
    HeapArray *array_form;
    HeapType type;
} Heap;

#endif