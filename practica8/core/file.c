#include <string.h>
#include "structs.h"
#include "functions.h"
#include "../util/const.h"


/*void capture_file_data(File *file){
    size_t len = 0;
    long read;

    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);

    printf("\n\rDime el nombre del archivo: ");
    read = getline(&(file->filename), &len, stdin);

    if (read == -1){
        file->filename = NULL;
        printf("\n\rNombre no valido...");
        return;
    }

    file->filename[strcspn(file->filename, "\n")] = 0;

    printf("\n\rDime la cantidad de paginas: ");
    scanf("%d", &(file->pages));
}*/

void capture_file_data(File *file){
    char buffer[256];

    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);

    printf("\n\rDime el nombre del archivo: ");
    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        file->filename = malloc(strlen(buffer) + 1);
        if (file->filename == NULL) {
            printf("\n\rNo se pudo asignar memoria para el nombre del archivo\n");
            return;
        }
        strcpy(file->filename, buffer);
    } else {
        file->filename = NULL;
        printf("\n\rNombre no valido...");
        return;
    }

    file->filename[strcspn(file->filename, "\n")] = 0;

    printf("\n\rDime la cantidad de paginas: ");
    scanf("%d", &(file->pages));
}

File *find_file (Mqueue *mqueue, int op){
    if (op < 0 )
        return NULL;

    File *found = NULL;

    int file_number = 0;

    for (int i = 0; i < mqueue->num_queues; i++){
        for(int j = 0; j < mqueue->start->num_nodes; j++){
            if (file_number == op)
                found = &(mqueue->start->start->file);
            file_number++;
            enqueue(mqueue->start, dequeue(mqueue->start));  
        }
        menqueue(mqueue, mdequeue(mqueue));
    }

    return found;
}

void delete_file(Mqueue *mqueue, File *file){
    if (file == NULL){
        printf("\n\rNo valido...");
        return;
    }
    
    int primordial_num_queues = mqueue->num_queues;
    for (int i = 0; i < primordial_num_queues; i++){
        int primordial_num_nodes = mqueue->start->num_nodes;
        for(int j = 0; j < primordial_num_nodes; j++){
            if (&(mqueue->start->start->file) == file){
                Node *aux = dequeue(mqueue->start);
                free(aux->file.filename);
                free(aux);
            } else {
                enqueue(mqueue->start, dequeue(mqueue->start));
            }
        }

        if (mqueue->start->num_nodes == 0){
            free(mdequeue(mqueue));
        } else {
            menqueue(mqueue, mdequeue(mqueue));
        }
    } 
}

void delete_all_files(Mqueue *mqueue, int running){
    if (mqueue->start == NULL){
        if (running != 0) printf("\n\rNo hay archivos...");
        return;
    }
   
    while (mqueue->start != NULL)
        delete_file(mqueue, &(mqueue->start->start->file));

    initialize_mqueue(mqueue);
}

void process_file(Mqueue *mqueue){
    if (mqueue->start == NULL){
        printf("\n\rNo hay archivos...");
        return;
    }

    File *comprob = &(mqueue->start->start->file);
    delete_file(mqueue, &(mqueue->start->start->file));

    if (mqueue->start == NULL || comprob != &(mqueue->start->start->file)) 
        printf("\n\rArchivo procesado...");
    else
        printf("\n\rArchivo no procesado...");   
}

