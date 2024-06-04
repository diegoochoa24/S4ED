#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct File {
    char *filename;
    short int pages;
} File;

typedef enum {
    MIN_HEAP,
    MAX_HEAP
} HeapType;

typedef struct QueueNode {
    File *file;
    size_t data_size;
    struct QueueNode *next;
} QueueNode;

typedef struct Queue {
    QueueNode *front;
    QueueNode *rear;
    short int num_nodes;
} Queue;

typedef struct TreeNode {
    Queue *queue;
    size_t data_size;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

typedef struct Tree {
    TreeNode *root;
    int level;
    int num_nodes;
} Tree;

typedef struct HeapTree {
    Tree *tree;
    HeapType type;
} HeapTree;

typedef struct HeapArray {
    File **elements;
    size_t element_size;
    int size;
    HeapType type;
} HeapArray;

typedef struct Heap {
    HeapTree *tree_form;
    HeapArray *array_form;
    int size;
    HeapType type;
} Heap;

// Function prototypes
void swap(File **a, File **b);
void heapifyDown(HeapArray *heap, int i);
void heapifyUp(HeapArray *heap, int i);
void insertHeapArray(HeapArray *heap, File *file);
File* extractHeapArray(HeapArray *heap);
void changePriority(HeapArray *heap);
void printQueue(HeapArray *heap);
void addFile(HeapArray *heap);
void deleteFile(HeapArray *heap);
void deleteAllFiles(HeapArray *heap);
void processPrintFile(HeapArray *heap);
