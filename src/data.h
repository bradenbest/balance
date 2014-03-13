#define DATA_H
#include "config.h"

#ifndef MAXFS
#  define MAXFS 10000
#endif

#ifndef FILENAME
#  define FILENAME ".balance_data"
#endif

typedef struct data{
  unsigned int dollar_bank : 32;
  unsigned int dollar_bank_extra : 32;
  unsigned int dollar_wallet : 32;
  unsigned int coin_q : 32;
  unsigned int coin_d : 32;
  unsigned int coin_n : 32;
  unsigned int coin_p : 32;
  unsigned int wage_next_hours : 32;
  unsigned int wage_next_minutes : 32;
  unsigned int wage_current_hours : 32;
  unsigned int wage_current_minutes : 32;
} data;

void file_copy(char *src, char *file);
void file_save(data *d, char *file);
void data_parse(data *d, char *src);

