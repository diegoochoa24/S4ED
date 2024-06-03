#ifndef HASH_H
#define HASH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "movie.h"


typedef int (*FunctionFolding)(void *, int); //POINTER TO A FUNCTION

typedef enum {
    INT_TYPE,
    STRING_TYPE
} hashType;

typedef struct hashtable
{
    hashType type;
    int size;          //DATOS QUE PUEDE CONTENER
    int amount_data; //DATOS CONTENIDOS
    Movie **table; //ALMACENAMIENTO
    FunctionFolding folding; //POINTER TO A FUNCTION FOLDING
}HashTable;

// Hash prototypes
int hash_id(void *movie_value, int size);
int hash_name(void *movie_value, int size);
HashTable* create_hash_table(int size, FunctionFolding folding);
int rehash(HashTable* hash_table, int id, int k);
void insert_movie(HashTable* hash_table, Movie* movie);
int delete_movie_by_id(HashTable* hash_table_id, HashTable* hash_table_name, int id, int non);
int delete_movie_by_name(HashTable* hash_table_id, HashTable* hash_table_name, char* name, int non);
Movie* search_movie_by_id(HashTable* hash_table, int id);
Movie* search_movie_by_name(HashTable* hash_table, char* name);
void print_hash_table(HashTable* hash_table);


#endif //HASH_H