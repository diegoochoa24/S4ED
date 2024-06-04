#include <stdio.h>
#include "app/components.h"

int main(void){

    App app;
    initialize_app(&app);

    while (app.running){
        menu(&app);
    }

    delete_hash_table(&app.hash_table_id);
    delete_hash_table(&app.hash_table_name);
    delete_array_movies(&app.movies, app.cant_movies);

    printf("\n\riii");
    return 0;
}

