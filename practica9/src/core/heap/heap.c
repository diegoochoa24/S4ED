#include "heap.h"


void initialize_heap(Heap *heap){
    heap->tree_form = (HeapTree*)calloc(1, sizeof(HeapTree));
    heap->array_form = (HeapArray*)calloc(1, sizeof(HeapArray));
    heap->size = 0;

    heap->tree_form->tree = (Tree*)calloc(1, sizeof(Tree));
    cast_heap_data(heap->array_form);

    initialize_tree(heap->tree_form->tree);
}

void set_heap_type(Heap *heap, HeapType type){
    heap->type = type;
    heap->tree_form->type = type;
    heap->array_form->type = type;
}

void print_heap_array(HeapArray *heapArray){
    printf("[");
    char comma;
    int **element = (int **)(heapArray->elements);
    for (int i = 0; i < heapArray->size; i++){
        int **element = (int **)(heapArray->elements);
        comma = i == heapArray->size - 1 ? ' ' : ',';
        printf(" ", get_heap_data(heapArray->elements[i]),  comma);

    }
    printf("}");
}



void print_heap(Heap *heap) {
    print_tree(heap->tree_form->tree->root, heap->tree_form->tree->level);
    print_heap_array(heap->array_form);
}


// Heap data functions
void cast_heap_data(HeapArray *heapArray){
    heapArray->elements = (int*)calloc(1, sizeof(int));

}

int get_heap_data(int element){

}