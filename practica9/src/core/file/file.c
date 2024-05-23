#include <string.h>
#include "../util/const.h"
#include "../../app/components.h"
#include "file.h"

void cast_file_data(QueueNode *node){
    node->data = (File*)calloc(1, sizeof(File));
    node->data_size = sizeof(File);
}

int capture_file_data(File *file){
    char buffer[256];

    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);

    printf("\n\rDime el nombre del archivo: ");
    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        file->filename = malloc(strlen(buffer) + 1);
        if (file->filename == NULL) {
            ERROR(MEMORY_ALLOCATION);
            return FALSE;
        }
        strcpy(file->filename, buffer);
    } else {
        file->filename = NULL;
        ERROR(INVALID_VALUE);
        return FALSE;
    }

    file->filename[strcspn(file->filename, "\n")] = 0;

    printf("\n\rDime la cantidad de paginas: ");
    scanf("%hu", &(file->pages));
    return TRUE;
}

void print_file_data(File *file, int *index){
    printf("\n\r[%d] %s (%d)", *index, file->filename, file->pages);
    (*index)++;
}
