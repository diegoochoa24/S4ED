
#include "components.h"
#include "../core/printer/print_queue.h"
#include "../util/const.h"


void initialize_app(App *app){
    app->heap = (Heap*)calloc(1, sizeof(Heap));
    initialize_heap(app->heap);
    set_heap_type(app->heap, MIN_HEAP);
    app->running = 1;
}

void menu(App *app){
    //system("cls"); //WINDOWS
    printf("\n\rP%d", app->heap->type);
    printf("\n\r [0] CAMBIAR PRIORIDAD");
    printf("\n\r [1] MOSTRAR COLA DE IMPRESION");
    printf("\n\r [2] AGREGAR ARCHIVO");
    printf("\n\r [3] ELIMINAR ARCHIVO");
    printf("\n\r [4] ELIMINAR TODOS LOS ARCHIVOS");
    printf("\n\r [5] PROCESAR/IMPRIMIR ARCHIVO");
    printf("\n\r [6] TERMINAR PROGRAMA");
    int op = INPUT();

    switch (op)
    {
        case 0:
            HeapType changetype = (app->heap->type == MIN_HEAP) ? MAX_HEAP : MIN_HEAP;
            set_heap_type(app->heap, changetype);
            break;
        case 1:
            printf("\n\rCola de impresion (%d): ", app->heap->size);
            print_heap(app->heap);
            break;
        case 2:
            add_file_to_print_queue(app->heap);
            break;
        case 3:
            //delete_option(app->heap);
            break;
        case 4:
            //delete_all_files(app->heap, app->running);
            break;
        case 5:
            //process_file(app->heap);
            break;
        case 6:
            app->running = FALSE;
            break;
        default:
            ERROR(INVALID_VALUE);
            break;
    }
    printf("\n\n\r");
    //system("pause"); //WINDOWS
}
/*
void delete_option(Mqueue *mqueue){
    if (mqueue->start == NULL){
        printf("\n\rNo hay archivos...");
        return;
    }

    printf("\n\rEliminar archivo:");
    print_mqueue(mqueue);

    int op = select_op();

    File *found = find_file(mqueue, op);  

    delete_file(mqueue, found);
}*/

int INPUT(){
    int op;
    printf("\n[INPUT] ");
    printf("\n\rEscoge una opcion: ");
    scanf("%d", &op);
    return op;
}

void INFO(InfoType type){
    printf("\n[INFO]: ");
    if (type == NO_FILES_ADDED)
        printf("No se han añadido archivos. \n");
}


void ERROR(ErrorType type){
    printf("\n[ERROR]: ");
    if (type == MEMORY_ALLOCATION) {
        printf("No se pudo asignar memoria. \n");
    } else if (type == INVALID_VALUE) {
        printf("Valor no válido. \n");
    } else {
        printf("Ha habido un error. \n");
    }
}
