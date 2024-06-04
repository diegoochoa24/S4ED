#include "components.h"
#include "../util/const.h"

void initialize_app(App *app) {
    app->cant_movies = 0;
    app->hash_table_id = create_hash_table(SIZE_DATA, hash_id);
    app->hash_table_id->type = INT_TYPE;
    app->hash_table_name = create_hash_table(SIZE_DATA * 4, hash_name);
    app->hash_table_name->type = STRING_TYPE;
    app->next_id = 106;
    app->running = TRUE;

    app->movies = create_movies();
    for (int i = 0; i < SIZE_DATA; i++) {
        insert_movie(app->hash_table_id, app->movies[i]);
        insert_movie(app->hash_table_name, app->movies[i]);
        app->cant_movies++;
    }
}

void menu(App *app) {
    printf("\n\r PRÁCTICA 10: HASH");
    printf("\n\r Factor de carga: %.2f", factor);
    printf("\n\r [0] MOSTRAR HASH ID");
    printf("\n\r [1] MOSTRAR HASH NOMBRE");
    printf("\n\r [2] BUSCAR PELÍCULA ID");
    printf("\n\r [3] BUSCAR PELÍCULA NOMBRE");
    printf("\n\r [4] AGREGAR PELÍCULA");
    printf("\n\r [5] ELIMINAR PELÍCULA");
    printf("\n\r [6] TERMINAR PROGRAMA");
    int op = INPUT("Selecciona una opción");

    int id;
    char *name;
    int year, rating;
    Movie* movie;

    switch (op) {
        case 0:
            print_hash_table(app->hash_table_id);
            break;
        case 1:
            print_hash_table(app->hash_table_name);
            break;
        case 2:
            id = INPUT("Introduce el ID de la película");
            movie = search_movie_by_id(app->hash_table_id, id);
            if (movie != NULL) {
                print_movie(movie);
            } else {
                ERROR(MOVIE_NOT_FOUND);
            }
            break;
        case 3:
            name = INPUT_STRING("Introduce el nombre de la película");
            movie = search_movie_by_name(app->hash_table_name,  name);
            if (movie != NULL) {
                print_movie(movie);
            } else {
                ERROR(MOVIE_NOT_FOUND);
            }
            free(name);
            break;
        case 4:
            name = INPUT_STRING("Introduce el nombre de la película");
            year = INPUT("Introduce el año de la película");
            rating = INPUT("Introduce la calificación de la película");

            app->movies = realloc(app->movies, (app->cant_movies + 1) * sizeof(Movie*));
            if (app->movies == NULL) {
                ERROR(MEMORY_ALLOCATION);
                break;
            }

            app->movies[app->cant_movies] = (Movie*)malloc(sizeof(Movie));
            if (app->movies[app->cant_movies] == NULL) {
                ERROR(MEMORY_ALLOCATION);
                free(name);
                break;
            }

            movie = app->movies[app->cant_movies];
            movie->id = app->next_id;
            movie->name = strdup(name);
            if (movie->name == NULL) {
                ERROR(MEMORY_ALLOCATION);
                free(movie);
                free(name);
                break;
            }

            movie->release_date = year;
            movie->rating = rating;
            app->cant_movies++;

            app->hash_table_id->table = realloc(app->hash_table_id->table, (app->hash_table_id->size + 1) * sizeof(Movie*));
            if (app->hash_table_id->table == NULL) {
                ERROR(MEMORY_ALLOCATION);
                break;
            }

            app->hash_table_id->table[app->hash_table_id->size] = NULL;
            app->hash_table_id->size++;

            Movie **temp_table = realloc(app->hash_table_name->table, (app->hash_table_name->size + 4) * sizeof(Movie*));
            if (temp_table == NULL) {
                ERROR(MEMORY_ALLOCATION);
                break;
            }
            app->hash_table_name->table = temp_table;

            for (int i = app->hash_table_name->size; i < app->hash_table_name->size + 4; i++) {
                app->hash_table_name->table[i] = NULL;
            }
            app->hash_table_name->size += 4;

            insert_movie(app->hash_table_id, movie);
            insert_movie(app->hash_table_name, movie);

            remap_hash(&(app->hash_table_id));
            remap_hash(&(app->hash_table_name));

            app->next_id++;

            INFO(MOVIE_ADDED);

            free(name);
            break;
        case 5:
            delete_menu(app);
            break;
        case 6:
            app->running = FALSE;
            break;
        default:
            ERROR(OPTION_VALUE);
            break;
    }
    printf("\n\n\r");
}

void delete_menu(App *app){
    int id;
    char *name;

    printf("Eliminar por:\n");
    printf("[1] ID\n");
    printf("[2] Nombre\n");
    int op = INPUT("Selecciona una opción");

    if (op == 1) {
        id = INPUT("Introduce el ID de la película");
        int eliminated = delete_movie_by_id(app->hash_table_id, app->hash_table_name, id, 0);

        remap_hash(&(app->hash_table_id));
        remap_hash(&(app->hash_table_name));

        if (eliminated == TRUE){
            INFO(MOVIE_DELETED);
        } else {
            ERROR(MOVIE_NOT_FOUND);
        }
    } else if (op == 2) {
        name = INPUT_STRING("Introduce el nombre de la película");
        int eliminated = delete_movie_by_name(app->hash_table_id, app->hash_table_name, name, 0);

        remap_hash(&(app->hash_table_id));
        remap_hash(&(app->hash_table_name));

        if (eliminated == TRUE){
            INFO(MOVIE_DELETED);
        } else {
            ERROR(MOVIE_NOT_FOUND);
        }

        free(name);
    } else {
        ERROR(OPTION_VALUE);
    }
}


//Console functions
int INPUT(char *message) {
    int op;
    printf("\n\r%s: ", message);
    printf("\n[INPUT]: ");
    fflush(stdout);
    scanf("%d", &op);
    fflush(stdout);
    return op;
}

char* INPUT_STRING(char *message) {

    printf("\n\r%s: ", message);
    printf("\n[INPUT]: ");

    char *str;
    char buffer[256];

    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);

    fflush(stdout);
    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        // Eliminar el salto de línea si está presente
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }

        str = malloc(len + 1);
        if (str == NULL) {
            ERROR(INVALID_VALUE);
            return NULL;
        }
        strcpy(str, buffer);
    } else {
        perror("Error de entrada");
        return NULL;
    }

    return str;
}

void INFO(InfoType type) {
    printf("\n[INFO]: ");
    if (type == MOVIE_ADDED) {
        printf("Película añadida. \n");
    } else if (type == MOVIE_DELETED) {
        printf("Película eliminada. \n");
    } else {
        printf("Información por mostrar. \n");
    }
}

void ERROR(ErrorType type) {
    printf("\n[ERROR]: ");
    if (type == MEMORY_ALLOCATION) {
        printf("No se pudo asignar memoria. \n");
    } else if (type == OPTION_VALUE) {
        printf("Opción no válido. \n");
    } else if (type == INVALID_VALUE) {
        printf("Valor no válido. \n");
    } else if (type == MOVIE_NOT_FOUND) {
        printf("Película no encontrada. \n");
    } else if (type == UNSIGNED_HASH_TYPE) {
        printf("Tipo de Hash no asignado. \n");
    } else {
        printf("Ha habido un error. \n");
    }
}
