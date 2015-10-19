#include <stdio.h>
#include <stdlib.h>

#include "balance.h"
#include "ui.h"
#include "history.h"

void history_destroy(edit_node **history){/*{{{*/
    edit_node **h = history;

    while(*h){
        free(*h);
        h++;
    }
    free(history);
}/*}}}*/
edit_node **history_new(int sz){/*{{{*/
    edit_node **history = calloc(sizeof(edit_node *), sz);
    return history;
}/*}}}*/
void history_push(edit_node **history, edit_node *node){/*{{{*/
    while(*history){
        history++;
    }
    *history = node;
}/*}}}*/
void history_report(edit_node **history){/*{{{*/
    int i = 0;
    edit_mode mode;
    char val_str[10];
    while(history[i]){
        mode = history[i]->mode;
        color_begin(col_white);
        printf("%3u  ", i+1);
        color_begin(col_yellow);
        printf("%-12s", edit_string(mode));
        color_begin(col_white);
        printf("%-18s", history[i]->fieldname);
        color_begin(col_blue);
        switch(mode){
            case edit_add:
            case edit_modify:
            case edit_time_shift:
                sprintf(val_str, "[%lu]", history[i]->value.l);
                printf("%-10s  ", val_str);
                color_end();
                printf( "%lu --> %lu\n",
                        history[i]->before.l,
                        history[i]->after.l);
                break;
            case edit_config:
                sprintf(val_str, "[%.2f]", history[i]->value.d);
                printf("%-10s  ", val_str);
                color_end();
                printf( "%.2f --> %.2f\n",
                        history[i]->before.d,
                        history[i]->after.d);
                break;
            default:
                return;
        }
        i++;
    }
}/*}}}*/
edit_node *node_new(edit_mode mode, char *fieldname, long_double value, long_double before, long_double after){/*{{{*/
    edit_node *node = calloc(sizeof(edit_node), 1);
    node->mode = mode;
    node->fieldname = fieldname;
    node->value = value;
    node->before = before;
    node->after = after;
    return node;
}/*}}}*/
