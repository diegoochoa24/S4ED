#pragma once 
#include <stdio.h>
#include <stdlib.h>
#include "../core/structs.h"


typedef struct app {
    Mqueue *mqueue;
    int running;
} App;


// components.c functions
void initialize_app(App *app);
void menu(App *app);
int select_op();
void add_option(Mqueue *mqueue);
void delete_option(Mqueue *mqueue);