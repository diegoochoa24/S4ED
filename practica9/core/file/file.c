#include <string.h>
#include "structs.h"
#include "functions.h"
#include "../util/const.h"


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

int print_file_data(File *file, int index){
    if (file == NULL){
        printf("\n\rNo valido...");
        return FALSE;
    }

    printf("\n\r[%d] %s (%d)", index, file->filename, file->pages);

    return TRUE;
}
