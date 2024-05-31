#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Movie.h"
#include "Hash.h"


int main(void)
{
    int i;
    HashTable myHash;
    Movie **movies = NULL;
    Movie *data = NULL;

    //EL SIGUIENTE CODIGO SOLO ES PARA DEMOSTRAR COMO OBTENDRAN LOS DATOS
    movies = create_movies();

    //DESPLEGAR
    for(i=0;i<SIZE_DATA;i++)
    {
        data = getMovie(movies,i);
        if(data)
        {
            printf("\n");
            printMovie(data);
        }
    }

    //LIBERAR MEMORIA
    for(i=0;i<SIZE_DATA;i++)
    {
        data = getMovie(movies,i);
        if(data)
        {
            free(data);
            movies[i]=NULL;
        }
    }

    free(movies);

    printf("\n\n");
    return 0;
}

