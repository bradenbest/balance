/* Write arbitrary values to file.*/
#include "../balance.h"
#include "../input.h"

int main(){
    data d = {
       42,   /* bank         */
       34,   /* bank2        */
        1,   /* wallet       */
        2,   /* quarters     */
        4,   /* dimes        */
        6,   /* nickels      */
        8,   /* pennies      */
       99,   /* next_minutes */
       88,   /* cur_minutes  */
        3.0, /* wage         */
        8.0, /* income_tax   */
    };
    data_save(&d);
    return 0;
}
