#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file.h"
#include "data.h"
#include "config.h"
#include "version.h"
#include "interface.h"
#include "get_home.h"

int main(int argc, char **argv){
  char *src;
  char fname[1000];
  data d;
  version v;

  set_version(&v);

  if(config.interface.DEBUG_MODE)    printf("DEBUG :: Checking for arguments.\n");
  if(argc > 1){ // Argument is passed
    strcpy(fname,argv[1]);
    if(config.interface.DEBUG_MODE)    printf("DEBUG :: Argument found\nDEBUG :: Trying argument \"%s\"\n", fname);
  }else{
    if(config.interface.DEBUG_MODE)    printf("DEBUG :: No arguments found\nDEBUG :: Checking for config.\n");
    if(config.data.FILENAME[0] != 0){ // File specified in config.c
      strcpy(fname,config.data.FILENAME);
      if(config.interface.DEBUG_MODE)    printf("DEBUG :: Config found\nDEBUG :: Trying config.data.FILENAME (\"%s\").\n", fname);
    }else{ // Neither an argument is passed, nor file specified. Default to checking $HOME
      get_home(fname);
      if(config.interface.DEBUG_MODE){
        printf("DEBUG :: No File Specified in config.\nDEBUG :: Defaulting to HOME environment variable (\"%s\"). If this fails, the program will segfault.\n", fname);
      }
    }
  }
  src = fcopy(fname);

  data_parse(&d,src);

  prompt(&d,&v,fname);

  return 0;
}
