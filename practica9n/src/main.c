#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct File {
    char *filename;
    short int pages;
} File;

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

typedef enum {
    MIN_HEAP,
    MAX_HEAP
} HeapType;

typedef struct HeapTree {
    Tree *tree;
    HeapType type;
} HeapTree;

typedef struct HeapArray {
    Queue **elements;
    size_t element_size;
    int size;
    int capacity;
    HeapType type;
} HeapArray;

typedef struct Heap {
    HeapTree *tree_form;
    HeapArray *array_form;
    int size;
    HeapType type;
} Heap;

// Function prototypes
Heap *createHeap(HeapType type);
void changePriority(Heap *heap);
void showPrintQueue(Heap *heap);
void addFile(Heap *heap, char *filename, short int pages);
void deleteFile(Heap *heap, int index);
void deleteAllFiles(Heap *heap);
void processPrintFile(Heap *heap);
void freeHeap(Heap *heap);
void heapify(HeapArray *heapArray, int i);
void swap(File **a, File **b);
void ensureCapacity(HeapArray *heapArray);
void insertHeapArray(HeapArray *heapArray, File *file);

void buildTreeFromHeapArray(HeapArray *heapArray, Tree *tree);
TreeNode* buildTreeRecursive(File **elements, int size, int index);



int main() {
    int choice;
    Heap *heap = createHeap(MIN_HEAP);

    do {
        printf("\nMenu:\n");
        printf("[0] CAMBIAR PRIORIDAD\n");
        printf("[1] MOSTRAR COLA DE IMPRESIÓN\n");
        printf("[2] AGREGAR ARCHIVO\n");
        printf("[3] ELIMINAR ARCHIVO\n");
        printf("[4] ELIMINAR TODOS LOS ARCHIVOS\n");
        printf("[5] PROCESAR/IMPRIMIR ARCHIVO\n");
        printf("[6] TERMINAR PROGRAMA\n");
        printf("Seleccione una opción: ");
        scanf("%d", &choice);

        switch (choice) {
            case 0:
                changePriority(heap);
                break;
            case 1:
                showPrintQueue(heap);
                break;
            case 2: {
                char filename[100];
                short int pages;
                printf("Ingrese el nombre del archivo: ");
                scanf("%s", filename);
                printf("Ingrese el número de páginas: ");
                scanf("%hd", &pages);
                addFile(heap, filename, pages);
                break;
            }
            case 3: {
                int index;
                printf("Ingrese el índice del archivo a eliminar: ");
                scanf("%d", &index);
                deleteFile(heap, index);
                break;
            }
            case 4:
                deleteAllFiles(heap);
                break;
            case 5:
                processPrintFile(heap);
                break;
            case 6:
                freeHeap(heap);
                break;
            default:
                printf("Opción no válida\n");
        }
    } while (choice != 6);

    return 0;
}

Heap *createHeap(HeapType type) {
    Heap *heap = (Heap *)malloc(sizeof(Heap));
    heap->tree_form = NULL;
    heap->array_form = (HeapArray *)malloc(sizeof(HeapArray));
    heap->array_form->elements = (File **)malloc(10 * sizeof(File *));
    heap->array_form->size = 0;
    heap->array_form->capacity = 10;
    heap->array_form->type = type;
    heap->type = type;
    return heap;
}

void changePriority(Heap *heap) {
    if (heap->type == MIN_HEAP) {
        heap->type = MAX_HEAP;
        heap->array_form->type = MAX_HEAP;
    } else {
        heap->type = MIN_HEAP;
        heap->array_form->type = MIN_HEAP;
    }

    for (int i = heap->array_form->size / 2 - 1; i >= 0; i--) {
        heapify(heap->array_form, i);
    }
    printf("Prioridad cambiada.\n");
}

void showPrintQueue(Heap *heap) {
    printf("Cola de impresión:\n");
    for (int i = 0; i < heap->array_form->size; i++) {
        printf("%d: %s - %d páginas\n", i, heap->array_form->elements[i]->filename, heap->array_form->elements[i]->pages);
    }
}

void addFile(Heap *heap, char *filename, short int pages) {
    File *file = (File *)malloc(sizeof(File));
    file->filename = strdup(filename);
    file->pages = pages;
    insertHeapArray(heap->array_form, file);
}

void deleteFile(Heap *heap, int index) {
    if (index < 0 || index >= heap->array_form->size) {
        printf("Índice inválido\n");
        return;
    }
    File *lastFile = heap->array_form->elements[heap->array_form->size - 1];
    heap->array_form->elements[index] = lastFile;
    heap->array_form->size--;
    heapify(heap->array_form, index);
    printf("Archivo eliminado.\n");
}

void deleteAllFiles(Heap *heap) {
    for (int i = 0; i < heap->array_form->size; i++) {
        free(heap->array_form->elements[i]->filename);
        free(heap->array_form->elements[i]);
    }
    heap->array_form->size = 0;
    printf("Todos los archivos eliminados.\n");
}

void processPrintFile(Heap *heap) {
    if (heap->array_form->size == 0) {
        printf("No hay archivos en la cola de impresión.\n");
        return;
    }
    File *file = heap->array_form->elements[0];
    printf("Imprimiendo archivo: %s - %d páginas\n", file->filename, file->pages);
    free(file->filename);
    free(file);
    heap->array_form->elements[0] = heap->array_form->elements[heap->array_form->size - 1];
    heap->array_form->size--;
    heapify(heap->array_form, 0);
}

void freeHeap(Heap *heap) {
    deleteAllFiles(heap);
    free(heap->array_form->elements);
    free(heap->array_form);
    free(heap);
    printf("Memoria liberada.\n");
}

void heapify(HeapArray *heapArray, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    int size = heapArray->size;

    if (heapArray->type == MIN_HEAP) {
        if (left < size && heapArray->elements[left]->pages < heapArray->elements[largest]->pages)
            largest = left;
        if (right < size && heapArray->elements[right]->pages < heapArray->elements[largest]->pages)
            largest = right;
    } else {
        if (left < size && heapArray->elements[left]->pages > heapArray->elements[largest]->pages)
            largest = left;
        if (right < size && heapArray->elements[right]->pages > heapArray->elements[largest]->pages)
            largest = right;
    }

    if (largest != i) {
        swap(&heapArray->elements[i], &heapArray->elements[largest]);
        heapify(heapArray, largest);
    }
}

void swap(File **a, File **b) {
    File *temp = *a;
    *a = *b;
    *b = temp;
}

void ensureCapacity(HeapArray *heapArray) {
    if (heapArray->size >= heapArray->capacity) {
        heapArray->capacity *= 2;
        heapArray->elements = (File **)realloc(heapArray->elements, heapArray->capacity * sizeof(File *));
    }
}

void insertHeapArray(HeapArray *heapArray, File *file) {
    ensureCapacity(heapArray);

    int index = heapArray->size;
    heapArray->elements[index] = file;
    heapArray->size++;

    while (index > 0) {
        int parentIndex = (index - 1) / 2;
        if (heapArray->type == MIN_HEAP) {
            if (heapArray->elements[index]->pages < heapArray->elements[parentIndex]->pages) {
                swap(&heapArray->elements[index], &heapArray->elements[parentIndex]);
                index = parentIndex;
            } else {
                break;
            }
        } else {
            if (heapArray->elements[index]->pages > heapArray->elements[parentIndex]->pages) {
                swap(&heapArray->elements[index], &heapArray->elements[parentIndex]);
                index = parentIndex;
            } else {
                break;
            }
        }
    }
}


void buildTreeFromHeapArray(HeapArray *heapArray, Tree *tree) {
    if (heapArray == NULL || tree == NULL) {
        printf("Arreglo de heap o árbol no válidos.\n");
        return;
    }

    // Liberar el árbol existente, si hay uno
    if (tree->root != NULL) {
        free(tree->root);
        tree->root = NULL;
        tree->num_nodes = 0;
    }

    // Construir el árbol a partir del arreglo de heap
    tree->root = buildTreeRecursive(heapArray->elements, heapArray->size, 0);
    tree->num_nodes = heapArray->size;
}

TreeNode* buildTreeRecursive(File **elements, int size, int index) {
    if (index >= size) {
        return NULL;
    }

    // Crear un nuevo nodo para el elemento en la posición actual
    TreeNode *newNode = (TreeNode *)malloc(sizeof(TreeNode));
    newNode->queue = NULL; // Inicializar la cola si es necesario
    newNode->data_size = sizeof(File);

    // Asignar el archivo al nodo
    newNode->file = (File *)malloc(sizeof(File));
    newNode->file->filename = strdup(elements[index]->filename);
    newNode->file->pages = elements[index]->pages;

    // Recursivamente construir los hijos izquierdo y derecho
    newNode->left = buildTreeRecursive(elements, size, 2 * index + 1);
    newNode->right = buildTreeRecursive(elements, size, 2 * index + 2);

    return newNode;
}

