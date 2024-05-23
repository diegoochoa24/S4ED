#include "heap.h"


void initialize_heap(Heap *heap){
    heap->tree_form = (HeapTree*)calloc(1, sizeof(HeapTree));
    heap->array_form = (HeapArray*)calloc(1, sizeof(HeapArray));
    heap->size = 0;

    initialize_tree(heap->tree_form->tree);
}

void set_heap_type(Heap *heap, HeapType type){
    heap->type = type;
    heap->tree_form->type = type;
    heap->array_form->type = type;
}



