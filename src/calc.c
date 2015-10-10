#include "balance.h"
#include "calc.h"

double calc_coin_total(data *d, coint_mode mode){/*{{{*/
    switch(mode){
        case coint_all:
            return 
                (d->quarters * 0.25) +
                (d->dimes    * 0.10) +
                (d->nickels  * 0.05) +
                (d->pennies  * 0.01);
        case coint_bank:
            return 
                ((d->quarters % 40) * 0.25) +
                ((d->dimes    % 50) * 0.10) +
                ((d->nickels  % 40) * 0.05) +
                ((d->pennies  % 50) * 0.01);
        case coint_rolls:
            return
                ((d->quarters - (d->quarters % 40)) * 0.25) +
                ((d->dimes    - (d->dimes    % 50)) * 0.10) +
                ((d->nickels  - (d->nickels  % 40)) * 0.05) +
                ((d->pennies  - (d->pennies  % 50)) * 0.01);
        default:
            break;
    }
    return 0;
}/*}}}*/
int calc_hours_portion(int minutes){/*{{{*/
    return minutes / 60;
}/*}}}*/
double calc_hours_total(int minutes){/*{{{*/
    int h = calc_hours_portion(minutes),
        m = calc_minutes_portion(minutes);
    return (double)h + (double)m / 60;
}/*}}}*/
int calc_minutes_portion(int minutes){/*{{{*/
    return minutes % 60;
}/*}}}*/
double calc_tax(data *d, wage_mode mode){/*{{{*/
    double wage = calc_wage(d, mode),
           tax  = d->income_tax;
    return wage * (tax / 100);
}/*}}}*/
double calc_wage(data *d, wage_mode mode){/*{{{*/
    int minutes = get_minutes_by_mode(d, mode);
    double wage = d->wage;

    return (double)minutes * (wage / 60);
}/*}}}*/
int get_minutes_by_mode(data *d, wage_mode mode){/*{{{*/
    switch(mode){
        case wage_next:
            return d->next_minutes;
        case wage_current:
            return d->cur_minutes;
        default:
            return 0;
    }
}/*}}}*/
