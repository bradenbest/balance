#include <stdio.h>
#include <stdlib.h>

#include "balance.h"
#include "input.h"
#include "ui.h"
#include "calc.h"
#include "history.h"

static char *coint_string(coint_mode mode);
static void edit_field(data *d, edit_node **history, edit_mode mode);
static field *get_field(data *d, edit_mode mode);
static void get_field_by_id(field *fields, field *f, edit_mode mode);
static void get_time();
static void print_coin_part(data *d, coint_mode mode);
static void print_help();
static void print_wage_part(data *d, wage_mode mode);
static void show_fields(field *fields, edit_mode mode);
static void time_shift(data *d, edit_node **history);

static char *coint_string(coint_mode mode){/*{{{*/
    switch(mode){
        case coint_all:   return "All";
        case coint_bank:  return "Bank";
        case coint_rolls: return "Rolls";
        default:          break;
    }
    return 0;
}/*}}}*/
static void edit_field(data *d, edit_node **history, edit_mode mode){/*{{{*/
    field *f = get_field(d, mode);
    long_double val,
                before,
                after;
    edit_node *node;
    if (!f){
        printf("Invalid number\n");
        return;
    }
    switch(mode){
        case edit_add:
            printf("Enter value to add to '%s' (current: %u): ", f->name, *f->value.l);
            scanf("%lu", &val.l);
            before.l = *f->value.l;
            *f->value.l += val.l;
            after.l = *f->value.l;
            break;
        case edit_modify:
            printf("Enter new value for '%s' (current: %u): ", f->name, *f->value.l);
            scanf("%lu", &val.l);
            before.l = *f->value.l;
            *f->value.l = val.l;
            after.l = *f->value.l;
            break;
        case edit_config:
            printf("Enter new value for '%s' (current: %.2f): ", f->name, *f->value.d);
            scanf("%lf", &val.d);
            before.d = *f->value.d;
            *f->value.d = val.d;
            after.d = *f->value.d;
            break;
        default:
            return;
    }
    node = node_new(mode, f->name, val, before, after);
    history_push(history, node);
    free(f);
}/*}}}*/
static field *get_field(data *d, edit_mode mode){/*{{{*/
    field fields[] = {
        { 1, "Bank",              {.l = &d->bank        }  },
        { 2, "Bank2",             {.l = &d->bank2       }  },
        { 3, "Wallet",            {.l = &d->wallet      }  },
        { 4, "Quarters",          {.l = &d->quarters    }  },
        { 5, "Dimes",             {.l = &d->dimes       }  },
        { 6, "Nickels",           {.l = &d->nickels     }  },
        { 7, "Pennies",           {.l = &d->pennies     }  },
        { 8, "Minutes (next)",    {.l = &d->next_minutes}  },
        { 9, "Minutes (current)", {.l = &d->cur_minutes }  },
        { 0 }
    };
    field confs[] = {
        { 1, "Hourly Wage",       {.d = &d->wage      }    },
        { 2, "Income Tax",        {.d = &d->income_tax}    },
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
                    f->value.l = fields[i].value.l;
                    break;
                case edit_config:
                    f->value.d = fields[i].value.d;
                    break;
                default:
                    break;
            }
            return;
        }
        i++;
    }
    f->id = 0;
}/*}}}*/
static void get_time(){/*{{{*/
    int hours   = 0,
        minutes = 0;
    fputs("Enter hours and minutes in hh:mm format: ", stdout);
    scanf("%u:%u", &hours, &minutes);
    printf("%u:%02u --> %u minutes\n", hours, minutes, (hours * 60) + minutes);
}/*}}}*/
static void print_coin_part(data *d, coint_mode mode){/*{{{*/
    int quarters,
        dimes,
        nickels,
        pennies;

    fputs("  ", stdout);
    color_print(col_white, coint_string(mode));
    putchar('\n');
    switch(mode){
        case coint_all:
            quarters = d->quarters;
            dimes    = d->dimes;
            nickels  = d->nickels;
            pennies  = d->pennies;
            break;
        case coint_bank:
            quarters = d->quarters % 40;
            dimes    = d->dimes    % 50;
            nickels  = d->nickels  % 40;
            pennies  = d->pennies  % 50;
            break;
        case coint_rolls:
            quarters = (d->quarters - (d->quarters % 40)) / 40;
            dimes    = (d->dimes    - (d->dimes    % 50)) / 50;
            nickels  = (d->nickels  - (d->nickels  % 40)) / 40;
            pennies  = (d->pennies  - (d->pennies  % 50)) / 50;
            break;
    }
    printf( "    Quarters: %u\n"
            "    Dimes:    %u\n"
            "    Nickels:  %u\n"
            "    Pennies:  %u\n"
            "    Total:    $%.2f\n",
            quarters,
            dimes,
            nickels,
            pennies,
            calc_coin_total(d, mode));
}/*}}}*/
static void print_help(){/*{{{*/
    puts("List of commands:\n"
            "  quit         q    exit the program\n"
            "  add          ad   add to a field\n"
            "  config       cfg  edit a config field\n"
            "  edit         ed   edit a field\n"
            "  get_time     gt   convert hh:mm to minutes\n"
            "  help         ?    print this help\n"
            "  history      hs   print history of edits this session\n"
            "  save         w    save and exit\n"
            "  show         sh   print a full report of the data\n"
            "  time_shift   ts   push current minutes to next minutes\n"
            "\n"
            "You can also quit by pressind Ctrl+D\n"
            "");
}/*}}}*/
static void print_wage_part(data *d, wage_mode mode){/*{{{*/
    int minutes;
    switch(mode){
        case wage_next:
            minutes = d->next_minutes;
            color_print(col_white, "  Next\n");
            break;
        case wage_current:
            minutes = d->cur_minutes;
            color_print(col_white, "  Current\n");
            break;
        default:
            return;
    }
    printf( "    %u:%02u (%.2f)\n"
            "      %.2f/hr\n"
            "      $%.2f (w/ tax: $%.2f)\n",
            calc_hours_portion(minutes),
            calc_minutes_portion(minutes),
            calc_hours_total(minutes),
            d->wage,
            calc_wage(d, mode),
            calc_wage(d, mode) - calc_tax(d, mode));

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
                printf(" ] %-30s%u\n", fields[i].name, *(fields[i].value.l));
                break;
            case edit_config:
                printf(" ] %-30s%.2f\n", fields[i].name, *(fields[i].value.d));
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
static void time_shift(data *d, edit_node **history){/*{{{*/
    edit_node *node1;
    edit_node *node2;
    long_double values[3] = {
        { .l = d->cur_minutes },
        { .l = d->next_minutes },
        { .l = 0 },
    };
    node1 = node_new(edit_time_shift, "Minutes (next)",    values[0], values[1], values[0]);
    node2 = node_new(edit_time_shift, "Minutes (current)", values[2], values[0], values[2]);
    printf( "This will do the following to your minutes:\n"
            "    Before: next = %u, current = %u\n"
            "    After:  next = %u, current = %u\n",
            d->next_minutes, d->cur_minutes,
            d->cur_minutes, 0);
    if(input_yes_or_no("Confirm operation? ", yes) == yes){
        d->next_minutes = d->cur_minutes;
        d->cur_minutes = 0;
        history_push(history, node1);
        history_push(history, node2);
        puts("Values have been shifted.");
    } else {
        puts("Aborted.");
    }
}/*}}}*/

void color_begin(color c){/*{{{*/
    if(USE_COLOR){
        color_end();
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
    }
}/*}}}*/
void color_print(color c, char *msg){/*{{{*/
    color_begin(c);
    fputs(msg, stdout);
    color_end();
}/*}}}*/
void color_end(){/*{{{*/
    if(USE_COLOR){
        fputs("\e[0m", stdout);
    }
}/*}}}*/
char *edit_string(edit_mode mode){/*{{{*/
    switch(mode){
        case edit_add:        return "Add";
        case edit_modify:     return "Edit";
        case edit_config:     return "Config";
        case edit_time_shift: return "Time Shift";
        default:              break;
    }
    return 0;
}/*}}}*/
void show_data(data *d){/*{{{*/
    color_print(col_blue, "Dollar\n");
    printf( "  Bank:   $%u\n"
            "          $%u\n"
            "  Wallet: $%u\n",
            d->bank, d->bank2, d->wallet);
    putchar('\n');

    color_print(col_blue, "Coin\n");
    print_coin_part(d, coint_all);
    print_coin_part(d, coint_bank);
    print_coin_part(d, coint_rolls);
    putchar('\n');

    color_print(col_blue, "Paycheck\n");
    print_wage_part(d, wage_next);
    print_wage_part(d, wage_current);
    putchar('\n');
}/*}}}*/
void ui_loop(data *d){/*{{{*/
    command cmd;
    edit_node **edit_history = history_new(100);
    while(1){
        fputs("Type 'help' for a list of commands.\n", stdout);
        color_print(col_none, "[");
        color_print(col_red,  "balance v" VERSION);
        color_print(col_none, "] ");
        color_print(col_blue, "> ");
        cmd = input_get_command(0);
        switch(cmd){
            case cmd_add:
                edit_field(d, edit_history, edit_add);
                break;
            case cmd_edit:
                edit_field(d, edit_history, edit_modify);
                break;
            case cmd_config:
                edit_field(d, edit_history, edit_config);
                break;
            case cmd_get_time:
                get_time();
                break;
            case cmd_help:
                print_help();
                break;
            case cmd_history:
                history_report(edit_history);
                break;
            case cmd_quit:
                if(input_yes_or_no("Save? ", yes) == yes){
                    puts("Saving before exit.");
                    data_save(d);
                }else{
                    puts("Exiting without save.");
                }
                goto end_of_loop;
            case cmd_save:
                puts("Saving and exiting.");
                data_save(d);
                goto end_of_loop;
            case cmd_show:
                show_data(d);
                break;
            case cmd_time_shift:
                time_shift(d, edit_history);
                break;
            default:
                break;
        }
    }
end_of_loop:
    history_destroy(edit_history);
    return;
}/*}}}*/
