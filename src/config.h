typedef struct{
  unsigned int MAXFS;
  char *FILENAME;
} data_conf;

typedef struct{
  unsigned int DEBUG_MODE : 1;
} inter_conf;

typedef struct{
  double WAGE;
  double INCOME_TAX;
} wage_conf;

typedef struct{
  data_conf data;
  inter_conf interface;
  wage_conf wage;
} global_conf;

const global_conf config;
