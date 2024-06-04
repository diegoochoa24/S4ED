#pragma once 
#include <stdio.h>
#include <stdlib.h>
#include "../core/heap/heap.h"


typedef struct app {
    Heap *heap;
    int running;
} App;

// components.c functions
void initialize_app(App *app);
void menu(App *app);
void add_option(Heap *heap);
void delete_option(Heap *heap);


typedef enum {
    NO_FILES_ADDED
} InfoType;

typedef enum {
    MEMORY_ALLOCATION,
    INVALID_VALUE
} ErrorType;

//console functions
int INPUT();
void INFO(InfoType type);
void ERROR(ErrorType type);