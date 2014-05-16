#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "data.h"
#include "config.h"

void file_save(data *d, char *file){
  FILE *f = fopen(file,"w");
  fprintf(f,
    "%010i,%010i,%010i,%010i,%010i,%010i,%010i,%010i,%010i,%010i,%010i",
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
  fclose(f);
}

static const char blank[11] = {0,0,0,0,0,0,0,0,0,0,0};
static const int dlen = 11;

static void get_val(char *buf, char *src, int index){
  int i = index * dlen,
      pos = 0;
  strcpy(buf,blank);
  while(pos < dlen-1){
    buf[pos] = src[i+pos];
    pos++;
  }
  buf[pos] = 0;
}

void data_parse(data *d, char *src){
  char buf[11];
  #define GV(i) get_val(buf,src,i)
  GV(0);  d->dollar_bank          = atoi(buf);
  GV(1);  d->dollar_bank_extra    = atoi(buf);
  GV(2);  d->dollar_wallet        = atoi(buf);
  GV(3);  d->coin_q               = atoi(buf);
  GV(4);  d->coin_d               = atoi(buf);
  GV(5);  d->coin_n               = atoi(buf);
  GV(6);  d->coin_p               = atoi(buf);
  GV(7);  d->wage_next_hours      = atoi(buf);
  GV(8);  d->wage_next_minutes    = atoi(buf);
  GV(9);  d->wage_current_hours   = atoi(buf);
  GV(10); d->wage_current_minutes = atoi(buf);
}
