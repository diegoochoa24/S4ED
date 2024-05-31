#ifndef FILE_H
#define FILE_H

#include <stdlib.h>


//File structure
typedef struct File
{
    char *filename;
    short int pages;
} File;

#include "../queue/queue.h"

//File prototypes
void cast_file_data(QueueNode *node);
int capture_file_data(File *file);
void print_file_data(File *file, int *index);

#endif
