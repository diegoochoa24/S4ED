#include <stdio.h>
#include "app/components.h"

int main(void){
    
    App app;
    initialize_app(&app);
    
    while (app.running){
        menu(&app);
    }
    
    //delete_all_files(app.mqueue, app.running);
    //free(app.mqueue);

    printf("\n\riii");
    return 0;
}
