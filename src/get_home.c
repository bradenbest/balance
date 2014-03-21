#include <string.h>
#include <stdlib.h>

#include "get_home.h"

void get_home(char *str){
  strcpy(str,getenv("HOME"));
  strcat(str,"/.balance_data");
}
