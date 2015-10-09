#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "balance.h"
#include "input.h"

void data_init(data *d){/*{{{*/
    d->bank         = 0;
    d->bank2        = 0;
    d->wallet       = 0;
    d->quarters     = 0;
    d->dimes        = 0;
    d->nickels      = 0;
    d->pennies      = 0;
    d->cur_minutes  = 0;
    d->next_minutes = 0;
    d->wage         = input_get_double("Enter value for hourly wage: ");
    d->income_tax   = input_get_double("Enter value for income tax: ");
}/*}}}*/
void data_load(data *d){/*{{{*/
    FILE *f;
    char fname[100];
    strcpy(fname, getenv("HOME"));
    strcat(fname, "/" FILENAME);
    f = fopen(fname, "rb");
    if(!f){ // File doesn't exist
        fputs("File ~/" FILENAME " doesn't exist. I will create it now.\n", stderr);
        data_init(d);
        data_save(d);
    } else {
        fread(d, sizeof(data), 1, f);
    }
    fclose(f);
}/*}}}*/
void data_save(data *d){/*{{{*/
    FILE *f;
    char fname[100];
    strcpy(fname, getenv("HOME"));
    strcat(fname, "/" FILENAME);
    f = fopen(fname, "wb");
    fwrite(d, sizeof(data), 1, f);
    fclose(f);
}/*}}}*/
