#include <stdlib.h>

#include "balance.h"
#include "input.h"
#include "ui.h"

int main(){
    data *d = malloc(sizeof(data));
    data_load(d);
    ui_loop(d);
    free(d);
    return 0;
}
