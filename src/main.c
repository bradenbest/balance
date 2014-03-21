#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "data.h"
#include "config.h"
#include "version.h"
#include "interface.h"

int main(int argc, char **argv){
  char src[config.data.MAXFS];
  char fname[1000];
  data d;
  version v;

  set_version(&v);

  if(argc > 1){ // Argument is passed
    strcpy(fname,argv[1]);
  }else{
    if(config.data.FILENAME[0] != 0){ // File specified in config.c
      strcpy(fname,config.data.FILENAME);
    }else{ // Neither an argument is passed, nor file specified. Default to checking $HOME
      get_home(fname);
    }
  }
  
  file_copy(src,fname);

  data_parse(&d,src);

  prompt(&d,&v,fname);

  return 0;
}
