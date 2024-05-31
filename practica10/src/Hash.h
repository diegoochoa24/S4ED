#ifndef HASH_H
#define HASH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Movie.h"


typedef int (*FunctionFolding)(Movie*); //POINTER A FUNCION


typedef struct hashtable
{
    int size;          //DATOS QUE PUEDE CONTENER
    int amount_data; //DATOS CONTENIDOS
    Movie **table; //ALMACENAMIENTO
    FunctionFolding folding; //POINTER A FUNCION FOLDING
}HashTable;


#endif //HASH_H