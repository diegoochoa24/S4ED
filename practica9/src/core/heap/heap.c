#include "heap.h"
#include "../../app/components.h"

void initialize_heap(Heap *heap){
    heap->tree_form = (HeapTree*)calloc(1, sizeof(HeapTree));
    heap->array_form = (HeapArray*)calloc(1, sizeof(HeapArray));
    heap->tree_form->tree = (Tree*)calloc(1, sizeof(Tree));
    heap->size = 0;

    initialize_tree(heap->tree_form->tree);
    initialize_heap_array(heap->array_form);
}

void set_heap_type(Heap *heap, HeapType type){
    heap->type = type;
    heap->tree_form->type = type;
    heap->array_form->type = type;
}

void print_heap_array(HeapArray *heapArray){
    printf("[");
    char comma;
    Queue **elements = (Queue **)(heapArray->elements);
    for (int i = 0; i < heapArray->size; i++){
        int j = 0;
        comma = i == heapArray->size - 1 ? ' ' : ',';
        printf(" (\n");
        print_queue(elements[i], &j);
        printf(" ) %c", comma);
    }
    printf("}");
}

void print_heap(Heap *heap) {
    if(heap->tree_form->tree->root == NULL){
        INFO(NO_FILES_ADDED);
        return;
    }

    print_tree(heap->tree_form->tree->root, heap->tree_form->tree->level);
    print_heap_array(heap->array_form);
}

// Heap data functions
void initialize_heap_array(HeapArray *heapArray){
    if (heapArray == NULL)
        return;

    heapArray->elements = (int*)calloc(1, sizeof(int));
    heapArray->element_size = sizeof(int);
    heapArray->size = 0;
}

void insert_array_data(HeapArray *heapArray, QueueNode *new_node){

    Queue **elements = (Queue **)(heapArray->elements);
    File *data_node = (File *)(new_node->data);

    for (int i = 0; i < heapArray->size; i++) {
        File *current_file = (elements[i]->front->data);
        if (current_file->pages == data_node->pages) {
            enqueue(elements[i], new_node);
            return;
        }
    }

    Queue *new_queue = (Queue*)calloc(1, sizeof(Queue));
    initialize_queue(new_queue);
    enqueue(new_queue, new_node);

    int new_size = heapArray->size + 1;
    heapArray->elements = realloc(heapArray->elements, new_size * sizeof(Queue*));

    File *front_data = (new_queue->front->data);

    // Insertar en la posición correcta
    int i;
    Queue *previous_element;
    File *previous_element_data;
    for (i = new_size - 1; i > 0 && ((heapArray->type == MIN_HEAP && front_data->pages < previous_element_data->pages) || (heapArray->type == MAX_HEAP && front_data->pages > previous_element_data->pages)); i--) {
        elements[i] = elements[i-1];
        previous_element = elements[i];
        previous_element_data = (File *)previous_element->front->data;
    }
    elements[i] = new_queue;
    heapArray->size = new_size;
}


void build_heap_tree(HeapTree *heapTree, HeapArray *heapArray){
    if (heapArray->size == 0) {
        heapTree->tree->root = NULL;
        return;
    }

    // Crear un array de TreeNodes
    TreeNode **nodes = (TreeNode**)malloc(heapArray->size * sizeof(TreeNode*));
    for (int i = 0; i < heapArray->size; i++) {
        Queue **elements = (Queue **)(heapArray->elements);
        nodes[i] = create_tree_node(elements[i]);
    }

    // Enlazar los TreeNodes para formar un árbol binario completo
    for (int i = 0; i < heapArray->size / 2; i++) {
        if (2 * i + 1 < heapArray->size) {
            nodes[i]->left = nodes[2 * i + 1];
        }
        if (2 * i + 2 < heapArray->size) {
            nodes[i]->right = nodes[2 * i + 2];
        }
    }

    // Establecer la raíz del árbol
    heapTree->tree->root = nodes[0];

    // Liberar memoria del array temporal
    free(nodes);
}
