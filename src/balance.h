#ifndef VERSION
#    define VERSION "2.0.0"
#endif

#ifndef USE_COLOR
#    define USE_COLOR 0
#endif

#ifndef FILENAME
#    define FILENAME ".balance-data"
#endif

typedef struct data {
    int    bank;
    int    bank2;
    int    wallet;

    int    quarters;
    int    dimes;
    int    nickels;
    int    pennies;

    int    next_minutes;
    int    cur_minutes;

    double wage;
    double income_tax;
} data;

typedef union {
    long l;
    double d;
} long_double;

typedef struct field {
    int id;
    char *name;
    int *ivalue;
    double *dvalue;
} field;

void data_init(data *d);
void data_load(data *d);
void data_save(data *d);
