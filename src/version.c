#include <stdio.h>

#include "version.h"

static const int MAJOR = 1;
static const int MINOR = 11;
static const int PATCH = 0;

void print_version(version *v){
  printf("Version ");
  if(v->patch){
    printf("%i.%i.%i\n", v->major, v->minor, v->patch);
  }else{
    printf("%i.%i\n", v->major, v->minor);
  }
}

void set_version(version *v){
  v->major = MAJOR;
  v->minor = MINOR;
  v->patch = PATCH;
}
