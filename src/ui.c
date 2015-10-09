#include <stdio.h>
#include <stdlib.h>

#include "balance.h"
#include "input.h"
#include "ui.h"
#include "calc.h"

static void edit_field(data *d, edit_mode mode);
static field *get_field(data *d, edit_mode mode);
static void get_field_by_id(field *fields, field *f, edit_mode mode);
static void print_help();
static void show_fields(field *fields, edit_mode mode);

static void edit_field(data *d, edit_mode mode){/*{{{*/
    field *f = get_field(d, mode);
    long_double val;
    if (!f){
        printf("Invalid number\n");
        return;
    }
    switch(mode){
        case edit_add:
            printf("Enter value to add to '%s' (current: %u): ", f->name, *f->ivalue);
            scanf("%lu", &val.l);
            *f->ivalue += val.l;
            break;
        case edit_modify:
            printf("Enter new value for '%s' (current: %u): ", f->name, *f->ivalue);
            scanf("%lu", &val.l);
            *f->ivalue = val.l;
            break;
        case edit_config:
            printf("Enter new value for '%s' (current: %.2f): ", f->name, *f->dvalue);
            scanf("%lf", &val.d);
            *f->dvalue = val.d;
            break;
        default:
            return;
    }
    free(f);
}/*}}}*/
static field *get_field(data *d, edit_mode mode){/*{{{*/
    field fields[] = {
        { 1, "Bank",              .ivalue = &d->bank          },
        { 2, "Bank2",             .ivalue = &d->bank2         },
        { 3, "Wallet",            .ivalue = &d->wallet        },
        { 4, "Quarters",          .ivalue = &d->quarters      },
        { 5, "Dimes",             .ivalue = &d->dimes         },
        { 6, "Nickels",           .ivalue = &d->nickels       },
        { 7, "Pennies",           .ivalue = &d->pennies       },
        { 8, "Minutes (next)",    .ivalue = &d->next_minutes  },
        { 9, "Minutes (current)", .ivalue = &d->cur_minutes   },
        { 0 }
    };
    field confs[] = {
        { 1, "Hourly Wage",       .dvalue = &d->wage          },
        { 2, "Income Tax",        .dvalue = &d->income_tax    },
        { 0 }
    };
    field *ret = malloc(sizeof(field));
    switch(mode){
        case edit_add:
        case edit_modify:
            show_fields(fields, mode);
            get_field_by_id(fields, ret, mode);
            break;
        case edit_config:
            show_fields(confs, mode);
            get_field_by_id(confs, ret, mode);
            break;
        default:
            break;
    }
    if(ret->id){
        return ret;
    } else {
        free(ret);
        return 0;
    }
}/*}}}*/
static void get_field_by_id(field *fields, field *f, edit_mode mode){/*{{{*/
    int fieldno = 0,
        i = 0;
    fputs("Enter the number of the field: ", stdout);
    scanf("%u", &fieldno);
    while(fields[i].id){
        if(fields[i].id == fieldno){
            f->name = fields[i].name;
            f->id = fields[i].id;
            switch(mode){
                case edit_add:
                case edit_modify:
                    f->ivalue = fields[i].ivalue;
                    break;
                case edit_config:
                    f->dvalue = fields[i].dvalue;
                    break;
            }
            return;
        }
        i++;
    }
    f->id = 0;
}/*}}}*/
static void print_help(){/*{{{*/
    puts("List of commands:\n"
            "  q, quit, ^D  exit the program\n"
            "  add          add to a field\n"
            "  config       edit a config field\n"
            "  edit         edit a field\n"
            "  h, help      print this help\n"
            "  history      print history of edits this session\n"
            "  save         save and exit\n"
            "  show         print a full report of the data\n"
            "");
}/*}}}*/
static void show_fields(field *fields, edit_mode mode){/*{{{*/
    char num[3];
    int i = 0,
        j;
    while(fields[i].id){
        sprintf(num, "%u", fields[i].id);
        fputs("[ ", stdout);
        color_print(col_yellow, num);
        switch(mode){
            case edit_add:
            case edit_modify:
                printf(" ] %-30s%u\n", fields[i].name, *(fields[i].ivalue));
                break;
            case edit_config:
                printf(" ] %-30s%.2f\n", fields[i].name, *(fields[i].dvalue));
                break;
            default:
                break;

        }
        if(fields[i+1].id){
            for(j = 0; j < 50; j++){
                putchar('-');
            }
        }
        putchar('\n');
        i++;
    }
}/*}}}*/

void color_print(color c, char *msg){/*{{{*/
    if(USE_COLOR){
        fputs("\e[", stdout);
        switch(c){
            case col_red:
                fputs("0;31;40m", stdout);
                break;
            case col_yellow:
                fputs("0;33;40m", stdout);
                break;
            case col_blue:
                fputs("0;34;40m", stdout);
                break;
            case col_white:
                fputs("1;37;40m", stdout);
                break;
            default:
                fputs("0m", stdout);
                break;
        }
        fputs(msg, stdout);
        fputs("\e[0m", stdout);
    } else {
        fputs(msg, stdout);
    }
}/*}}}*/
void show_data(data *d){/*{{{*/
    color_print(col_blue, "Dollar\n");
    printf( "  Bank:   $%u\n"
            "          $%u\n"
            "  Wallet: $%u\n",
            d->bank, d->bank2, d->wallet);
    putchar('\n');

    color_print(col_blue, "Coin\n");
    color_print(col_white, "  All\n");
    printf( "    Quarters: %u\n"
            "    Dimes:    %u\n"
            "    Nickels:  %u\n"
            "    Pennies:  %u\n"
            "    Total:    $%.2f\n",
            d->quarters,
            d->dimes,
            d->nickels,
            d->pennies,
            calc_coin_total(d, coint_all));

    color_print(col_white, "  Bank\n");
    printf( "    Quarters: %u\n"
            "    Dimes:    %u\n"
            "    Nickels:  %u\n"
            "    Pennies:  %u\n"
            "    Total:    $%.2f\n",
            d->quarters % 40,
            d->dimes    % 50,
            d->nickels  % 40,
            d->pennies  % 50,
            calc_coin_total(d, coint_bank));

    color_print(col_white, "  Rolls\n");
    printf( "    $10.00 (x40) Quarters: %u\n"
            "    $ 5.00 (x50) Dimes:    %u\n"
            "    $ 2.00 (x40) Nickels:  %u\n"
            "    $ 0.50 (x50) Pennies:  %u\n"
            "    ------------ Total:    $%.2f\n",
            d->quarters - (d->quarters % 40),
            d->dimes    - (d->dimes    % 50),
            d->nickels  - (d->nickels  % 40),
            d->pennies  - (d->pennies  % 50),
            calc_coin_total(d, coint_rolls));
    putchar('\n');

    color_print(col_blue, "Paycheck\n");
    color_print(col_white, "  Next\n");
    printf( "    %u:%02u (%.2f)\n"
            "      %.2f/hr\n"
            "      $%.2f (w/ tax: $%.2f)\n",
            calc_hours_portion(d->next_minutes),
            calc_minutes_portion(d->next_minutes),
            calc_hours_total(d->next_minutes),
            d->wage,
            calc_wage(d, wage_next),
            calc_tax(d, wage_next));

    color_print(col_white, "  Current\n");
    printf( "    %u:%02u (%.2f)\n"
            "      %.2f/hr\n"
            "      $%.2f (w/ tax: $%.2f)\n",
            calc_hours_portion(d->cur_minutes),
            calc_minutes_portion(d->cur_minutes),
            calc_hours_total(d->cur_minutes),
            d->wage,
            calc_wage(d, wage_current),
            calc_tax(d, wage_current));
    putchar('\n');
}/*}}}*/
void ui_loop(data *d){
    command cmd;
    while(1){
        fputs("Type 'help' for a list of commands.\n", stdout);
        color_print(col_none, "[");
        color_print(col_red,  "balance v" VERSION);
        color_print(col_none, "] ");
        color_print(col_blue, "> ");
        cmd = input_get_command(0);
        switch(cmd){
            case cmd_add:/*{{{*/
                edit_field(d, edit_add);
                break;/*}}}*/
            case cmd_edit:/*{{{*/
                edit_field(d, edit_modify);
                break;/*}}}*/
            case cmd_config:/*{{{*/
                edit_field(d, edit_config);
                break;/*}}}*/
            case cmd_help:/*{{{*/
                print_help();
                break;/*}}}*/
            case cmd_history:
                break;
            case cmd_quit:/*{{{*/
                if(input_yes_or_no("Save? ", yes) == yes){
                    puts("Saving before exit.");
                    data_save(d);
                }else{
                    puts("Exiting without save.");
                }
                goto end_of_loop;/*}}}*/
            case cmd_save:/*{{{*/
                data_save(d);
                goto end_of_loop;/*}}}*/
            case cmd_show:/*{{{*/
                show_data(d);
                break;/*}}}*/
            default:
                break;
        }
    }
end_of_loop:
    return;
}
