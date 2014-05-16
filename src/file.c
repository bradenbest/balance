#include <stdio.h>
#include <stdlib.h>

#include "file.h"

int fsize(FILE *f){
  int out;
  fseek(f,0,SEEK_END);
  out = ftell(f);
  fseek(f,0,SEEK_SET);
  return out;
}

char *fcopy(char *fname){
  FILE *f = fopen(fname, "r");
  int sz = fsize(f), 
      i = 0, 
      c;
  char *out = malloc(sizeof(char) * sz);
  while((c = getc(f)) != EOF)
    out[i++] = c;
  out[i] = 0;
  fclose(f);
  return out;
}
