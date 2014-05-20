#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"
#include "data.h"

typedef struct command_map {
  char *name;
  void (* function)(data *, FILE *);
  char *description;
} command_map;

typedef struct field_map {
  char *name;
  unsigned long *value;
} field_map;

void help_function(data *, FILE *);
void exit_function(data *, FILE *);
void save_function(data *, FILE *);
void edit_function(data *, FILE *);
void add_function(data *, FILE *);
void show_function(data *, FILE *);

command_map commands[] = {
    { "help", help_function, "displays this help message" },
    { "exit", exit_function, "exit the program without saving" },
    { "save", save_function, "save current data and exit" },
    { "edit", edit_function, "edit data" },
    { "add",  add_function,  "add to data" },
    { "show", show_function, "print a report with the existing data" } };

int command_map_compare(const void *x, const void *y) {
  return strcmp(((const command_map *) x)->name,
                ((const command_map *) y)->name);
}

void help_function(data *d, FILE *f) {
  puts("Commands:");
  for (size_t x = 0; x < sizeof commands / sizeof *commands; x++) {
    printf("%s\t-- %s\n", commands[x].name, commands[x].description);
  }
}

void exit_function(data *d, FILE *f) {
  fclose(f);
  exit(0);
}

void save_function(data *d, FILE *f) {
  rewind(f);
  fprintf(f,
    "%010lu,%010lu,%010lu,%010lu,%010lu,%010lu,%010lu,%010lu,%010lu,%010lu,%010lu\n",
    d->dollar_bank,
    d->dollar_bank_extra,
    d->dollar_wallet,
    d->coin_q,
    d->coin_d,
    d->coin_n,
    d->coin_p,
    d->wage_next_hours,
    d->wage_next_minutes,
    d->wage_current_hours,
    d->wage_current_minutes
  );
  exit_function(d, f);
}

int select_field(field_map *f, data *d) {
  field_map fields[] = {
    { "Dollar bank", &d->dollar_bank },
    { "Dollar bank (extra)", &d->dollar_bank_extra },
    { "Dollar wallet", &d->dollar_wallet },
    { "Quarter coins", &d->coin_q },
    { "Dime coins", &d->coin_d },
    { "Nickel coins", &d->coin_n },
    { "Penny coins", &d->coin_p },
    { "Wage next hours", &d->wage_next_hours },
    { "Wage next minutes", &d->wage_next_minutes },
    { "Wage current hours", &d->wage_current_hours },
    { "Wage current minutes", &d->wage_current_minutes } };

  for (size_t x = 0; x < sizeof fields / sizeof *fields; x++) {
    printf("Enter %zu for %s\n", x, fields[x].name);
  }

  unsigned long x = 0;
  if (scanf("%lu", &x) != 1 || x >= sizeof fields / sizeof *fields) {
    puts("Invalid selection.");
    for (int c = getchar(); c >= 0 && c != '\n'; c = getchar());
    return 0;
  }

  *f = fields[x];
  return 1;
}

void edit_function(data *d, FILE *f) {
  field_map field;
  if (!select_field(&field, d)) {
    return;
  }

  unsigned long new_value;
  printf("Enter new value for %s\n", field.name);
  if (scanf("%lu", &new_value) != 1) {
    puts("Invalid value.");
    for (int c = getchar(); c >= 0 && c != '\n'; c = getchar());
    return;
  }

  *field.value = new_value;
}

void add_function(data *d, FILE *f) {
  field_map field;
  if (!select_field(&field, d)) {
    return;
  }

  unsigned long increase;
  printf("Enter increase for %s\n", field.name);
  if (scanf("%lu", &increase) != 1) {
    puts("Invalid value.");
    for (int c = getchar(); c >= 0 && c != '\n'; c = getchar());
    return;
  }

  *field.value += increase;
}

void show_function(data *d, FILE *f) {
    unsigned long q_remainder = d->coin_q % 40, q_rolls = d->coin_q / 40,
                  d_remainder = d->coin_d % 50, d_rolls = d->coin_d / 50,
                  n_remainder = d->coin_n % 40, n_rolls = d->coin_n / 40,
                  p_remainder = d->coin_p % 50, p_rolls = d->coin_p / 50;

    unsigned long long coin_total = (unsigned long long) d->coin_q * 4ULL
                                  + (unsigned long long) d->coin_d * 10ULL
                                  + (unsigned long long) d->coin_n * 20ULL
                                  + (unsigned long long) d->coin_p * 100ULL,
                       remainder_total = (unsigned long long) q_remainder * 4ULL
                                       + (unsigned long long) d_remainder * 10ULL
                                       + (unsigned long long) n_remainder * 20ULL
                                       + (unsigned long long) p_remainder * 100ULL,
                       rolls_total = (unsigned long long) q_rolls * 4ULL
                                   + (unsigned long long) d_rolls * 10ULL
                                   + (unsigned long long) n_rolls * 20ULL
                                   + (unsigned long long) p_rolls * 100ULL;
    printf("Dollar{\n"
           "  Bank:   $%lu\n"
           "          $%lu\n"
           "  Wallet: $%lu\n"
           "}\n\n"
           "Coin{\n"
           "  All{\n"
           "    Quarters:\t%02lu\n"
           "    Dimes:\t%02lu\n"
           "    Nickels:\t%02lu\n"
           "    Pennies:\t%02lu\n"
           "    Total:\t$%llu.%02llu\n"
           "  }\n"
           "  Bank{\n"
           "    Quarters:\t%02lu\n"
           "    Dimes:\t%02lu\n"
           "    Nickels:\t%02lu\n"
           "    Pennies:\t%02lu\n"
           "    Total:\t$%llu.%02llu\n"
           "  }\n"
           "  Rolls{\n"
           "    Quarters:\t%02lu\n"
           "    Dimes:\t%02lu\n"
           "    Nickels:\t%02lu\n"
           "    Pennies:\t%02lu\n"
           "    Total:\t$%llu.%02llu\n"
           "  }\n"
           "}\n\n", d->dollar_bank, d->dollar_bank_extra, d->dollar_wallet
                  , d->coin_q, d->coin_d, d->coin_n, d->coin_p, coin_total / 100ULL, coin_total % 100ULL
                  , q_remainder, d_remainder, n_remainder, p_remainder, remainder_total / 100ULL, remainder_total % 100ULL
                  , q_rolls, d_rolls, n_rolls, p_rolls, rolls_total / 100ULL, rolls_total % 100ULL);
}

int main(int argc, char **argv){
  char fname[PATH_MAX + 1];
  data d;

  int path_len = snprintf(fname, PATH_MAX, "%s/.balance", argc > 1                        ? argv[1]
                                                        : config.data.FILENAME[0] != '\0' ? config.data.FILENAME
                                                                                          : getenv("HOME"));

  assert(path_len <= PATH_MAX); /* XXX: An actual error message should appear when this assertion fails. */

  FILE *f = fopen(fname, "w+");
  
  int items = fscanf(f,
    "%lu,%lu,%lu,%lu,%lu,%lu,%lu,%lu,%lu,%lu,%lu",
    &d.dollar_bank,
    &d.dollar_bank_extra,
    &d.dollar_wallet,
    &d.coin_q,
    &d.coin_d,
    &d.coin_n,
    &d.coin_p,
    &d.wage_next_hours,
    &d.wage_next_minutes,
    &d.wage_current_hours,
    &d.wage_current_minutes);

  if (items != 11) {
    d = (data) { 0 };
    puts("WARNING! fscanf() indicated that EOF or a read error was reached.");
    puts("If this is the first time you've run this program, ignore this error.");
    puts("Otherwise, ask the developer for assistance.");
    puts("---------------------------------------------------------------------");
  }

  command_map *selection;
  qsort(commands, sizeof commands / sizeof *commands, sizeof *commands, command_map_compare);
  help_function(&d, f);

  for (;;) {
    char cmd[11];
    switch (scanf("%10s", cmd)) {
      case 1:  selection = bsearch(&(command_map){ cmd }, commands, sizeof commands / sizeof *commands, sizeof *commands, command_map_compare);
               if (selection == NULL) { 
      default:   puts("Invalid command. Try again...");
                 for (int c = getchar(); c >= 0 && c != '\n'; c = getchar());
                 break;
               }

               selection->function(&d, f);
               break;
      case EOF:puts("EOF in stdin. Bye-bye!");
               exit(0);
    }
  }
}
