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
    int release_date;
    int rating;
}Movie;

//Movie functions
Movie** create_movies(void);
void print_movie(Movie *movie);
Movie* get_movie(Movie **movies,int index);

void delete_array_movies(Movie ***movies, int size);

#endif //MOVIE_H