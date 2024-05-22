#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "core/structs.h"
#include "core/functions.h"
#include "app/components.h"

int main(void){
    
    App app;
    initialize_app(&app);
    
    while (app.running){
        menu(&app);
    }
    
    delete_all_files(app.mqueue, app.running);
    free(app.mqueue);

    printf("\n\rii");
    return 0;
}
