#define INTERFACE_H
#include "config.h"

#ifndef DEBUG_MODE
#  define DEBUG_MODE 0
#endif

#define BLUE "\033[1;34;40m"
#define YELLOW "\033[1;33;40m"
#define DEFAULT "\033[0;37;40m"

void prompt(data *d, version *v, char *fname);
