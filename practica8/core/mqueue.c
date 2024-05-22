#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"
#include "functions.h"
#include "../util/const.h"


void initialize_mqueue(Mqueue *mqueue){
    mqueue->start = NULL;
    mqueue->end = NULL;
    mqueue->num_queues = 0;
}

void menqueue(Mqueue *mqueue, Queue *new_queue){
    if (mqueue->num_queues == 0)
        mqueue->start = new_queue;

    if (mqueue->end != NULL)
        mqueue->end->next = new_queue;

    mqueue->end = new_queue;    
    new_queue->next = NULL; 
    mqueue->num_queues++; 
}

Queue *mdequeue(Mqueue *mqueue){
    Queue *aux;
    aux = mqueue->start;
    if (mqueue->start->next != NULL){
        mqueue->start = mqueue->start->next;
        mqueue->num_queues--;
    } else {
        initialize_mqueue(mqueue);
    }
    aux->next = NULL;
    return aux;
}

void print_mqueue(Mqueue *mqueue){
    if (mqueue->start == NULL){
        printf("\n\rNo hay archivos...");
        return;
    }
    int num_file = 0;
    
    for(int i = 0; i < mqueue->num_queues; i++){   
        print_queue(mqueue->start, &num_file);
        menqueue(mqueue, mdequeue(mqueue));
    }
}

void sort_mqueue(Mqueue *mqueue){
    if (mqueue->start == NULL)
        return;
    
    Mqueue *mqueue_aux = (Mqueue*)calloc(1, sizeof(Mqueue));
    initialize_mqueue(mqueue_aux);

    menqueue(mqueue_aux, mdequeue(mqueue));
    while (mqueue->start != NULL){      
        if (mqueue->compare(mqueue->start->start->file.pages, mqueue_aux->start->start->file.pages)){
            menqueue(mqueue_aux, mdequeue(mqueue));
            for(int i = 0; i < (mqueue_aux->num_queues - 1); i++)
                menqueue(mqueue_aux, mdequeue(mqueue_aux));
        } else if (mqueue->compare(mqueue_aux->end->start->file.pages, mqueue->start->start->file.pages)){
            menqueue(mqueue_aux, mdequeue(mqueue));
        } else { 
            while (mqueue->compare(mqueue_aux->start->start->file.pages, mqueue->start->start->file.pages))
                menqueue(mqueue_aux, mdequeue(mqueue_aux));

            menqueue(mqueue_aux, mdequeue(mqueue));

            while (mqueue->compare(mqueue_aux->end->start->file.pages, mqueue_aux->start->start->file.pages))
                menqueue(mqueue_aux, mdequeue(mqueue_aux));
        }
    }

    while (mqueue_aux->start != NULL){
        menqueue(mqueue, mdequeue(mqueue_aux));
    }

    return;
}
