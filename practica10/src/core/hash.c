#include "hash.h"
#include "../app/components.h"
#include "../util/const.h"


//Folding functions
int hash_id(void *movie_value, int size){
    int *id = (int *)movie_value;
    return *id % size;
}

int hash_name(void *movie_value, int size) {
    char *name = (char *)movie_value;
    int hash = 0;

    for (int i = 0; name[i] != '\0'; i++) {
        hash += name[i];
    }

    return hash % size;
}


//Hash functions
HashTable* create_hash_table(int size, FunctionFolding folding) {
    HashTable* hash_table = (HashTable*)malloc(sizeof(HashTable));
    hash_table->size = size;
    hash_table->amount_data = 0;
    hash_table->table = (Movie**)calloc(size, sizeof(Movie*));
    hash_table->folding = folding;
    return hash_table;
}

void insert_movie(HashTable* hash_table, Movie* movie) {
    int index;
    if (hash_table->type == INT_TYPE){
        index = hash_table->folding(&(movie->id), hash_table->size);
    } else if (hash_table->type == STRING_TYPE){
        index = hash_table->folding(movie->name, hash_table->size);
    } else {
        ERROR(UNSIGNED_HASH_TYPE);
        return;
    }

    int new_index = index;
    int inserted = FALSE;
    int k = 1;

    while (inserted == FALSE) {
        if (hash_table->table[new_index] == NULL) {
            hash_table->table[new_index] = movie;
            hash_table->amount_data++;
            inserted = TRUE;
        } else {
            new_index = rehash(hash_table, index, k);
            k++;
        }
    }
}

int rehash(HashTable* hash_table, int id, int k){
    if (hash_table->type == INT_TYPE)
        return hash_table->amount_data;

    int new_index = (id + k * k) % hash_table->size;
    return new_index;
}

int delete_movie_by_id(HashTable* hash_table_id, HashTable* hash_table_name, int id, int non){
    int index = hash_id(&id, hash_table_id->size);

    int new_index = index;
    int eliminated = FALSE;
    int k = 1;

    while (1) {
        if (hash_table_id->table[new_index] == NULL){
            ERROR(MOVIE_NOT_FOUND);
            return eliminated;
        } else if (hash_table_id->table[new_index]->id == id) {
            if (non == 0){
                delete_movie_by_name(hash_table_id, hash_table_name, hash_table_id->table[new_index]->name, 1);
                free(hash_table_id->table[new_index]);
            }

            hash_table_id->table[new_index] = NULL;
            hash_table_id->amount_data--;
            eliminated = TRUE;
            return eliminated;
        } else {
            new_index = rehash(hash_table_id, index, k);
            k++;
        }
    }
}

int delete_movie_by_name(HashTable* hash_table_id, HashTable* hash_table_name, char* name, int non) {
    int index = hash_name(name, hash_table_name->size);

    int new_index = index;
    int eliminated = FALSE;
    int k = 1;

    while (1) {
        if (hash_table_name->table[new_index] == NULL){
            ERROR(MOVIE_NOT_FOUND);
            return eliminated;
        } else if (strcmp(hash_table_name->table[new_index]->name, name) == 0) {
            if (non == 0){
                delete_movie_by_id(hash_table_id, hash_table_name, hash_table_name->table[new_index]->id, 1);
                free(hash_table_name->table[new_index]);
            }

            hash_table_name->table[new_index] = NULL;
            hash_table_name->amount_data--;
            eliminated = TRUE;
            return eliminated;
        } else {
            new_index = rehash(hash_table_id, index, k);
            k++;
        }
    }
}

Movie* search_movie_by_id(HashTable* hash_table, int id) {
    int index = hash_id(&id, hash_table->size);

    int new_index = index;
    int k = 1;

    while (1) {
        if (hash_table->table[new_index] == NULL){
            return NULL;
        } else if (hash_table->table[new_index]->id == id) {
            return hash_table->table[new_index];
        } else {
            new_index = rehash(hash_table, index, k);
            k++;
        }
    }
}

Movie* search_movie_by_name(HashTable* hash_table, char* name) {
    int index = hash_name(name, hash_table->size);

    int new_index = index;
    int k = 1;

    while (1) {
        if (hash_table->table[new_index] == NULL){
            return NULL;
        } else if (strcmp(hash_table->table[new_index]->name, name) == 0) {
            return hash_table->table[new_index];
        } else {
            new_index = rehash(hash_table, index, k);
            k++;
        }
    }
}

void print_hash_table(HashTable* hash_table) {
    printf("\n");
    for (int i = 0; i < hash_table->size; i++) {
        if (hash_table->table[i] != NULL) {
            print_movie(hash_table->table[i]);
            printf("\n");
        }
    }
}

