
#include "components.h"
#include "../core/structs.h"
#include "../core/functions.h"
#include "../util/const.h"


void initialize_app(App *app){
    app->mqueue = (Mqueue*)calloc(1, sizeof(Mqueue));
    initialize_mqueue(app->mqueue);
    app->mqueue->priority = 0;
    set_priority(app->mqueue);
}

void menu(App *app){

    system("cls"); //WINDOWS 
    printf("\n\rP%d", app->mqueue->priority);
    printf("\n\r [0] CAMBIAR PRIORIDAD");
    printf("\n\r [1] MOSTRAR COLA DE IMPRESION");
    printf("\n\r [2] AGREGAR ARCHIVO");
    printf("\n\r [3] ELIMINAR ARCHIVO");
    printf("\n\r [4] ELIMINAR TODOS LOS ARCHIVOS");
    printf("\n\r [5] PROCESAR/IMPRIMIR ARCHIVO");
    printf("\n\r [6] TERMINAR PROGRAMA");

    int op = select_op();

    switch (op)
    {
        case 0:
            app->mqueue->priority = (app->mqueue->priority == 0) ? 1 : 0;
            set_priority(app->mqueue);
            sort_mqueue(app->mqueue);
            break;
        case 1:
            printf("\n\rCola de impresion (%d): ", app->mqueue->num_queues);
            print_mqueue(app->mqueue);
            break;
        case 2:
            add_option(app->mqueue);
            break;
        case 3:
            delete_option(app->mqueue);
            break;
        case 4:
            delete_all_files(app->mqueue, app->running);
            break;
        case 5:
            process_file(app->mqueue);
            break;
        case 6:
            app->running = FALSE;
            break;
        default:
            printf("\n\rNo valido...");
            break;
    }
    printf("\n\n\r");
    system("pause"); //WINDOWS
}

int select_op(){
    int op;
    printf("\n\rEscoge opcion: ");
    scanf("%d", &op);
    return op;
}

void add_option(Mqueue *mqueue){
    Node *node = create_node();
    
    if(node == NULL){
        printf("\n\rValores no validos...");
        return;
    }

    add_node(mqueue, node);
}

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
}

