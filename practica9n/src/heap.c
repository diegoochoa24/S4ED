
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"
#include "functions.h"

File *create_file(const char *filename, short int pages) {
    File *file = (File *)malloc(sizeof(File));
    file->filename = strdup(filename);
    file->pages = pages;
    return file;
}


Node *create_node(File *file) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->file = file;
    node->left = NULL;
    node->right = NULL;
    return node;
}

HeapArray *create_heap_array(int capacity, HeapType type) {
    HeapArray *heap_array = (HeapArray *)malloc(sizeof(HeapArray));
    heap_array->elements = (Node **)malloc(capacity * sizeof(Node *));
    heap_array->size = 0;
    heap_array->capacity = capacity;
    heap_array->type = type;
    return heap_array;
}

HeapTree *create_heap_tree(HeapType type) {
    HeapTree *heap_tree = (HeapTree *)malloc(sizeof(HeapTree));
    heap_tree->root = NULL;
    heap_tree->level = 0;
    heap_tree->num_nodes = 0;
    heap_tree->type = type;
    return heap_tree;
}

Heap *create_heap(int capacity, HeapType type) {
    Heap *heap = (Heap *)malloc(sizeof(Heap));
    heap->tree_form = create_heap_tree(type);
    heap->array_form = create_heap_array(capacity, type);
    heap->type = type;
    return heap;
}

void change_priority(Heap *heap) {
    heap->type = (heap->type == MIN_HEAP) ? MAX_HEAP : MIN_HEAP;
    heap->tree_form->type = heap->type;
    heap->array_form->type = heap->type;

    for (int i = heap->array_form->size / 2 - 1; i >= 0; i--) {
        heapify(heap->array_form, i);
    }

    free(heap->tree_form);
    heap->tree_form = create_heap_tree_from_array(heap->array_form);
}

void heapify(HeapArray *heap_array, int index) {
    int size = heap_array->size;
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    int extreme = index;

    if (heap_array->type == MIN_HEAP) {
        if (left < size && heap_array->elements[left]->file->pages < heap_array->elements[extreme]->file->pages)
            extreme = left;
        if (right < size && heap_array->elements[right]->file->pages < heap_array->elements[extreme]->file->pages)
            extreme = right;
    } else {
        if (left < size && heap_array->elements[left]->file->pages > heap_array->elements[extreme]->file->pages)
            extreme = left;
        if (right < size && heap_array->elements[right]->file->pages > heap_array->elements[extreme]->file->pages)
            extreme = right;
    }

    if (extreme != index) {
        Node *temp = heap_array->elements[index];
        heap_array->elements[index] = heap_array->elements[extreme];
        heap_array->elements[extreme] = temp;
        heapify(heap_array, extreme);
    }
}

void insert_file(Heap *heap, File *file) {
    HeapArray *heap_array = heap->array_form;
    if (heap_array->size == heap_array->capacity) {
        heap_array->capacity *= 2;
        heap_array->elements = realloc(heap_array->elements, heap_array->capacity * sizeof(Node *));
    }

    Node *new_node = create_node(file);
    heap_array->size++;
    int index = heap_array->size - 1;
    heap_array->elements[index] = new_node;

    while (index != 0) {
        int parent = (index - 1) / 2;
        if ((heap->type == MIN_HEAP && heap_array->elements[index]->file->pages >= heap_array->elements[parent]->file->pages) ||
            (heap->type == MAX_HEAP && heap_array->elements[index]->file->pages <= heap_array->elements[parent]->file->pages)) {
            break;
        }
        Node *temp = heap_array->elements[index];
        heap_array->elements[index] = heap_array->elements[parent];
        heap_array->elements[parent] = temp;
        index = parent;
    }

    free(heap->tree_form);
    heap->tree_form = create_heap_tree_from_array(heap->array_form);
}

void show_print_queue(Heap *heap) {
    if(heap->array_form->size == 0){
        printf("Heap vacia. \n");
        return;
    }

    printf("\n");
    HeapArray *heap_array = heap->array_form;
    for (int i = 0; i < heap_array->size; i++) {
        printf("[%d] %s (%d)\n", i, heap_array->elements[i]->file->filename, heap_array->elements[i]->file->pages);
    }

    printf("\n");
    print_tree(heap->tree_form->root, 0);
    printf("\n");

}

void delete_file(Heap *heap, int index) {
    HeapArray *heap_array = heap->array_form;

    if (index >= heap_array->size)
        return;

    heap_array->elements[index] = heap_array->elements[heap_array->size - 1];
    heap_array->size--;
    heapify(heap_array, index);

    free(heap->tree_form);
    heap->tree_form = create_heap_tree_from_array(heap->array_form);
}

void free_tree_nodes(Node *node) {
    if (node == NULL)
        return;
    free_tree_nodes(node->left);
    free_tree_nodes(node->right);
    free(node->file->filename);
    free(node->file);
    free(node);
}

void delete_all_files(Heap *heap) {

    for (int i = 0; i < heap->array_form->size; i++) {
        free(heap->array_form->elements[i]->file->filename);
        free(heap->array_form->elements[i]->file);
        free(heap->array_form->elements[i]);
    }
    heap->array_form->size = 0;
    heap->tree_form->root = NULL;
    heap->tree_form->num_nodes = 0;
}

void process_file(Heap *heap) {
    if (heap->array_form->size == 0) {
        printf("No hay archivos.\n");
        return;
    }
    File *file = heap->array_form->elements[0]->file;
    printf("Procesando archivo: %s (%d)\n", file->filename, file->pages);
    delete_file(heap, 0);

}

void free_heap(Heap *heap) {
    delete_all_files(heap);
    free(heap->array_form->elements);
    free(heap->array_form);
    free(heap->tree_form);
    free(heap);
}


HeapTree *create_heap_tree_from_array(HeapArray *heap_array) {
    if (heap_array->size == 0)
        return NULL;

    HeapTree *heap_tree = create_heap_tree(heap_array->type);

    heap_tree->root = build_tree(heap_array, 0);
    heap_tree->num_nodes = heap_array->size;
    return heap_tree;
}

Node* build_tree(HeapArray *heap_array,int index) {
    if (index >= heap_array->size)
        return NULL;

    Node **nodes = heap_array->elements;
    Node *node = nodes[index];
    node->left = build_tree(heap_array, 2 * index + 1);
    node->right = build_tree(heap_array, 2 * index + 2);
    return node;
}

void print_tree(Node* node, int level){
    int i;
    if (node != NULL)
    {
        printf("%s [%d]", node->file->filename, node->file->pages);
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
