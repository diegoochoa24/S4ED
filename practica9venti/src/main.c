#include "imp/structs.h"

void showMenu() {
    printf("------ MENÚ ------\n");
    printf("[0] CAMBIAR PRIORIDAD\n");
    printf("[1] MOSTRAR COLA DE IMPRESIÓN\n");
    printf("[2] AGREGAR ARCHIVO\n");
    printf("[3] ELIMINAR ARCHIVO\n");
    printf("[4] ELIMINAR TODOS LOS ARCHIVOS\n");
    printf("[5] PROCESAR/IMPRIMIR ARCHIVO\n");
    printf("[6] TERMINAR PROGRAMA\n");
    printf("-------------------\n");
}

int main() {
    HeapArray heap;
    heap.size = 0;
    heap.type = MIN_HEAP;
    heap.element_size = sizeof(File*);
    heap.elements = (File**)malloc(100 * sizeof(File*));

    int option;
    do {
        showMenu();
        printf("Seleccione una opción: ");
        scanf("%d", &option);

        switch (option) {
            case 0:
                changePriority(&heap);
            break;
            case 1:
                printQueue(&heap);
            break;
            case 2:
                addFile(&heap);
            break;
            case 3:
                deleteFile(&heap);
            break;
            case 4:
                deleteAllFiles(&heap);
            break;
            case 5:
                processPrintFile(&heap);
            break;
            case 6:
                printf("Terminando programa...\n");
            break;
            default:
                printf("Opción inválida.\n");
            break;
        }
    } while (option != 6);

    deleteAllFiles(&heap);
    free(heap.elements);
    return 0;
}
