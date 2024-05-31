#include <stdio.h>
#include "../util/const.h"
#include "../file/file.h"
#include "../queue/queue.h"
#include "../tree/tree.h"
#include "heap.h"

void add_file_to_print_queue(Heap *heap){
    QueueNode *new_queue_node = create_queue_node();

    insert_array_data(heap->array_form, new_queue_node);
    build_heap_tree(heap->tree_form, heap->array_form);

    heap->size++;
}
