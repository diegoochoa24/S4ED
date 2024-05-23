#include "queue.h"

void cast_queue_data(QueueNode *node){
    cast_file_data(node);
}

int capture_queue_data(File *file){
    return capture_file_data(file);
}

void print_queue_data(File *file, int *index){
    print_file_data(file, index);
}
