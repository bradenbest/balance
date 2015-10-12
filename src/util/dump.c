#include <stdio.h>

#include "../balance.h"
#include "../input.h"

int main(){
    data d = {0};
    data_load(&d);
    printf( "bank:         %u\n"
            "bank2:        %u\n"
            "wallet:       %u\n"
            "\n"           
            "quarters:     %u\n"
            "dimes:        %u\n"
            "nickels:      %u\n"
            "pennies:      %u\n"
            "\n"
            "next_minutes: %u\n"
            "cur_minutes:  %u\n"
            "\n"
            "wage:         %.2f\n"
            "income_tax:   %.2f\n",
            d.bank,
            d.bank2,
            d.wallet,
            
            d.quarters,
            d.dimes,
            d.nickels,
            d.pennies,

            d.next_minutes,
            d.cur_minutes,

            d.wage,
            d.income_tax);
    return 0;
}
