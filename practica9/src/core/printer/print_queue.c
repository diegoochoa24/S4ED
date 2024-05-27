#include <stdio.h>
#include "../util/const.h"
#include "../file/file.h"
#include "../queue/queue.h"
#include "../tree/tree.h"
#include "heap.h"

void add_file_to_print_queue(Heap *heap){
    QueueNode *new_queue_node = create_queue_node();




    insert_tree_data(heap->tree_form->tree, &(heap->tree_form->tree->root), new_queue_node);



    heap->size++;
}
