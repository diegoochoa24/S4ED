
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "structs.h"

File *create_file(const char *filename, short int pages);
Node *create_node(File *file);
HeapArray *create_heap_array(int capacity, HeapType type);
HeapTree *create_heap_tree(HeapType type);
Heap *create_heap(int capacity, HeapType type);
void change_priority(Heap *heap);
void heapify(HeapArray *heap_array, int index);
void insert_file(Heap *heap, File *file);
void show_print_queue(Heap *heap);
void delete_file(Heap *heap, int index);
void delete_all_files(Heap *heap);
void process_file(Heap *heap);
void free_heap(Heap *heap);
HeapTree *create_heap_tree_from_array(HeapArray *heap_array);
Node* build_tree(HeapArray *heap_array,int index);
void print_tree(Node* node, int level);



#endif
