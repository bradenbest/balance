/* Write arbitrary values to file. */
#include "../balance.h"
#include "../input.h"

int main(){
    data d = {
        0,   /* bank         */
        0,   /* bank2        */
        0,   /* wallet       */
        0,   /* quarters     */
        0,   /* dimes        */
        0,   /* nickels      */
        0,   /* pennies      */
        0,   /* next_minutes */
        0,   /* cur_minutes  */
        0.0, /* wage         */
        0.0, /* income_tax   */
    };
    data_save(&d);
    return 0;
}
