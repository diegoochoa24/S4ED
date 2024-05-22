#include <stdio.h>
#include <stdlib.h>
#include "../core/structs.h"
#include "../core/functions.h"
#include "const.h"


int compare_m2M(int m, int M){
    if (m < M){
        return TRUE;
    } else {
        return FALSE;
    }
}

int compare_M2m(int m, int M){
    if (M < m){
        return TRUE;
    } else {
        return FALSE;
    }
}

void set_priority(Mqueue *mqueue){
    if (mqueue->priority == 0){
        mqueue->compare = compare_m2M;
    } else {
        mqueue->compare = compare_M2m;
    }
}
