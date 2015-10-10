#ifndef VERSION
#    define VERSION "2.0.0"
#endif

#ifndef USE_COLOR
#    define USE_COLOR 0
#endif

#ifndef FILENAME
#    define FILENAME ".balance-data"
#endif

typedef struct data data;
typedef union long_double long_double;
typedef union long_double_ptr long_double_ptr;
typedef union long_double_ptr ldptr;
typedef struct field field;

void data_init(data *d);
void data_load(data *d);
void data_save(data *d);

struct data {
    int     bank;
    int     bank2;
    int     wallet;
            
    int     quarters;
    int     dimes;
    int     nickels;
    int     pennies;
            
    int     next_minutes;
    int     cur_minutes;
            
    double  wage;
    double  income_tax;
};

union long_double {
    long    l;
    double  d;
};

union long_double_ptr {
    int     *l;
    double  *d;
};

struct field {
    int    id;
    char   *name;
    ldptr  value;
};
