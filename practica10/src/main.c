#include <stdio.h>
#include "app/components.h"

int main(void){

    App app;
    initialize_app(&app);

    while (app.running){
        menu(&app);
    }
    //Liberar memoria

    printf("\n\riii");
    return 0;
}

