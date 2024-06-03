#pragma once 
#include <stdio.h>
#include <stdlib.h>
#include "../core/hash.h"

typedef struct app {
    HashTable *hash_table_id;
    HashTable *hash_table_name;
    int next_id;
    int running;
} App;

// components.c functions
void initialize_app(App *app);
void menu(App *app);
void delete_menu(App *app);

typedef enum {
    MOVIE_ADDED,
    MOVIE_DELETED
} InfoType;

typedef enum {
    MEMORY_ALLOCATION,
    OPTION_VALUE,
    INVALID_VALUE,
    MOVIE_NOT_FOUND,
    UNSIGNED_HASH_TYPE
} ErrorType;

//console functions
int INPUT(char *message);
char* INPUT_STRING(char *message);
void INFO(InfoType type);
void ERROR(ErrorType type);