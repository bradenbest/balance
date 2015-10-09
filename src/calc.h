typedef enum {
    coint_all,
    coint_bank,
    coint_rolls,
} coint_mode;

typedef enum {
    wage_next,
    wage_current,
} wage_mode;

double calc_coin_total(data *d, coint_mode mode);
int calc_hours_portion(int minutes);
double calc_hours_total(int minutes);
int calc_minutes_portion(int minutes);
double calc_tax(data *d, wage_mode mode);
double calc_wage(data *d, wage_mode mode);
int get_minutes_by_mode(data *d, wage_mode mode);
