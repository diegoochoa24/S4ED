#include "structs.h"

void swap(File **a, File **b) {
    File *temp = *a;
    *a = *b;
    *b = temp;
}

void heapifyDown(HeapArray *heap, int i) {
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    int smallestOrLargest = i;

    if (heap->type == MIN_HEAP) {
        if (left < heap->size && heap->elements[left]->pages < heap->elements[smallestOrLargest]->pages)
            smallestOrLargest = left;
        if (right < heap->size && heap->elements[right]->pages < heap->elements[smallestOrLargest]->pages)
            smallestOrLargest = right;
    } else {
        if (left < heap->size && heap->elements[left]->pages > heap->elements[smallestOrLargest]->pages)
            smallestOrLargest = left;
        if (right < heap->size && heap->elements[right]->pages > heap->elements[smallestOrLargest]->pages)
            smallestOrLargest = right;
    }

    if (smallestOrLargest != i) {
        swap(&heap->elements[i], &heap->elements[smallestOrLargest]);
        heapifyDown(heap, smallestOrLargest);
    }
}

void heapifyUp(HeapArray *heap, int i) {
    int parent = (i - 1) / 2;

    if (heap->type == MIN_HEAP) {
        if (i > 0 && heap->elements[i]->pages < heap->elements[parent]->pages) {
            swap(&heap->elements[i], &heap->elements[parent]);
            heapifyUp(heap, parent);
        }
    } else {
        if (i > 0 && heap->elements[i]->pages > heap->elements[parent]->pages) {
            swap(&heap->elements[i], &heap->elements[parent]);
            heapifyUp(heap, parent);
        }
    }
}

void insertHeapArray(HeapArray *heap, File *file) {
    // Aseguramos que hay suficiente espacio en el array
    if (heap->size >= heap->element_size) {
        heap->element_size *= 2;
        heap->elements = realloc(heap->elements, heap->element_size * sizeof(File*));
        if (heap->elements == NULL) {
            printf("Error: no se pudo redimensionar el heap.\n");
            exit(EXIT_FAILURE);
        }
    }

    // Insertamos el nuevo elemento al final del array
    int currentIndex = heap->size;
    heap->elements[currentIndex] = file;
    heap->size++;

    // Aplicamos heapifyUp para mantener la propiedad del heap
    int parentIndex = (currentIndex - 1) / 2;
    while (currentIndex != 0 &&
           ((heap->type == MIN_HEAP && heap->elements[currentIndex]->pages < heap->elements[parentIndex]->pages) ||
            (heap->type == MAX_HEAP && heap->elements[currentIndex]->pages > heap->elements[parentIndex]->pages))) {
        swap(&heap->elements[currentIndex], &heap->elements[parentIndex]);
        currentIndex = parentIndex;
        parentIndex = (currentIndex - 1) / 2;
            }
}




File* extractHeapArray(HeapArray *heap) {
    if (heap->size == 0)
        return NULL;

    File *root = heap->elements[0];
    heap->elements[0] = heap->elements[heap->size - 1];
    heap->size--;
    heapifyDown(heap, 0);

    return root;
}

void changePriority(HeapArray *heap) {
    if (heap->type == MIN_HEAP) {
        heap->type = MAX_HEAP;
    } else {
        heap->type = MIN_HEAP;
    }

    for (int i = heap->size / 2 - 1; i >= 0; i--) {
        heapifyDown(heap, i);
    }
}

void printQueue(HeapArray *heap) {
    printf("Cola de impresión:\n");
    for (int i = 0; i < heap->size; i++) {
        printf("Archivo: %s, Páginas: %d\n", heap->elements[i]->filename, heap->elements[i]->pages);
    }
}

void addFile(HeapArray *heap) {
    char filename[100];
    int pages;

    printf("Ingrese el nombre del archivo: ");
    scanf("%s", filename);
    printf("Ingrese el número de páginas: ");
    scanf("%d", &pages);

    File *file = (File*)malloc(sizeof(File));
    file->filename = strdup(filename);
    file->pages = pages;

    insertHeapArray(heap, file);
}

void deleteFile(HeapArray *heap) {
    printQueue(heap);
    int index;
    printf("Ingrese el índice del archivo a eliminar: ");
    scanf("%d", &index);

    if (index >= 0 && index < heap->size) {
        free(heap->elements[index]->filename);
        free(heap->elements[index]);
        heap->elements[index] = heap->elements[heap->size - 1];
        heap->size--;
        heapifyDown(heap, index);
    } else {
        printf("Índice inválido.\n");
    }
}

void deleteAllFiles(HeapArray *heap) {
    for (int i = 0; i < heap->size; i++) {
        free(heap->elements[i]->filename);
        free(heap->elements[i]);
    }
    heap->size = 0;
}

void processPrintFile(HeapArray *heap) {
    File *file = extractHeapArray(heap);
    if (file != NULL) {
        printf("Procesando archivo: %s, Páginas: %d\n", file->filename, file->pages);
        free(file->filename);
        free(file);
    } else {
        printf("No hay archivos en la cola de impresión.\n");
    }
}
