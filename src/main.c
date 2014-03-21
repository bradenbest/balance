#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "data.h"
#include "config.h"
#include "version.h"
#include "interface.h"

int main(int argc, char **argv){
  char src[config.data.MAXFS];
  char fname[100];
  data d;
  version v;

  set_version(&v);

  if(argc > 1)    strcpy(fname,argv[1]);
  else            strcpy(fname,config.data.FILENAME);
  
  file_copy(src,fname);

  data_parse(&d,src);

  prompt(&d,&v,fname);

  return 0;
}
