#include <stdio.h>
#include "app/components.h"

int main(void){
    
    App app;
    initialize_app(&app);
    
    while (app.running){
        menu(&app);
    }

    printf("\n\rii");
    return 0;
}
