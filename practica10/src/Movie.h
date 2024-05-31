#ifndef MOVIE_H
#define MOVIE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE_DATA 105

typedef struct 
{
    int id;
    char *name;
    short int release_date;
    short int rating;
}Movie;



//FUNCIONES DE PELICULAS
Movie** create_movies(void);
void printMovie(Movie *movie);
Movie* getMovie(Movie **movies,int index);



#endif //MOVIE_H