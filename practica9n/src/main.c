#include <stdio.h>
#include "structs.h"
#include "functions.h"

int main() {
    Heap *heap = create_heap(3, MIN_HEAP);
    int option;
    char filename[100];
    int pages;

    do {
        printf("\n[0] CAMBIAR PRIORIDAD\n");
        printf("[1] MOSTRAR COLA DE IMPRESIÓN\n");
        printf("[2] AGREGAR ARCHIVO\n");
        printf("[3] ELIMINAR ARCHIVO\n");
        printf("[4] ELIMINAR TODOS LOS ARCHIVOS\n");
        printf("[5] PROCESAR/IMPRIMIR ARCHIVO\n");
        printf("[6] TERMINAR PROGRAMA\n");
        printf("Seleccione una opción: ");
        scanf("%d", &option);

        switch(option) {
            case 0:
                change_priority(heap);
                printf("Prioridad cambiada.\n");
                break;
            case 1:
                show_print_queue(heap);
                break;
            case 2:
                printf("Ingrese nombre del archivo: ");
                scanf("%s", filename);
                printf("Ingrese número de páginas: ");
                scanf("%d", &pages);
                insert_file(heap, create_file(filename, pages));
                printf("Archivo agregado.\n");
                break;
            case 3:
                show_print_queue(heap);
                printf("Ingrese el índice del archivo a eliminar: ");
                int index;
                scanf("%d", &index);
                delete_file(heap, index);
                printf("Archivo eliminado.\n");
                break;
            case 4:
                delete_all_files(heap);
                printf("Todos los archivos han sido eliminados.\n");
                break;
            case 5:
                process_file(heap);
                break;
            case 6:
                free_heap(heap);
                printf("Programa terminado.\n");
                break;
            default:
                printf("Opción no válida.\n");
                break;
        }
    } while(option != 6);

    return 0;
}

