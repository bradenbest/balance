// Headers
// wagecalc /*{{{*/
double calcWage(int minutes, double wage);
int timeInMinutes(int hours, int minutes);
double timeInHours(int hours, int minutes);
double tax(double gross);/*}}}*/
// version/*{{{*/
typedef struct version{
  unsigned int major : 32;
  unsigned int minor : 32;
  unsigned int patch : 32;
} version;

void print_version(version *v);
void set_version(version *v);
/*}}}*/
// interface/*{{{*/
#define BLUE "\033[1;34;40m"
#define YELLOW "\033[1;33;40m"
#define DEFAULT "\033[0;37;40m"

void prompt(data *d, version *v, char *fname);
/*}}}*/
//get_home/*{{{*/
void get_home(char *str);
/*}}}*/
//data/*{{{*/
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
/*}}}*/
//config/*{{{*/
typedef struct{
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
/*}}}*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// code
// wagecalc/*{{{*/
double calcWage(int minutes, double wage){
  return (double)minutes * (wage / 60);
}

int timeInMinutes(int hours, int minutes){
  return (hours * 60) + minutes;
}

double timeInHours(int hours, int minutes){
  return (double)hours + ((double)minutes / 60);
}

double tax(double gross){
  return gross * (config.wage.INCOME_TAX / 100);
}
/*}}}*/
// version/*{{{*/
static const int MAJOR = 1;
static const int MINOR = 11;
static const int PATCH = 1;

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

/* This file should go in interface.h
 * Only thing that is necessary: #define VERSION "1.11.1"
 *//*}}}*/
// interface/*{{{*/

#define ENV_PROMPT(X) printf("Enter New Value for " X "\n" YELLOW "--> " DEFAULT); if(scanf(" %d", &new_val) == -1)    break // Enter New Value Prompt
#define EAV_PROMPT(X) printf("Enter Value to Add to " X "\n" YELLOW "--> " DEFAULT); if(scanf(" %d", &new_val) == -1)    break // Enter Add Value Prompt

static void render(data *d){
  // Dollar
  int db = d->dollar_bank;
  int dbe = d->dollar_bank_extra;
  int dw = d->dollar_wallet;

  // Coin
  int cq = d->coin_q;
  int cd = d->coin_d;
  int cn = d->coin_n;
  int cp = d->coin_p;

  // Coin reMainders
  int cmq = cq % 40;
  int cmd = cd % 50;
  int cmn = cn % 40;
  int cmp = cp % 50;

  // Coin Rolls
  int crq = (d->coin_q - d->coin_q % 40) / 40;
  int crd = (d->coin_d - d->coin_d % 50) / 50;
  int crn = (d->coin_n - d->coin_n % 40) / 40;
  int crp = (d->coin_p - d->coin_p % 50) / 50;

  // coin totals
  double c_total = cq * 0.25 + cd * 0.10 + cn * 0.05 + cp * 0.01;
  double cm_total = cmq * 0.25 + cmd * 0.10 + cmn * 0.05 + cmp * 0.01;
  double cr_total = crq * 10 + crd * 5 + crn * 2 + crp * 0.5;

  // wage next
  int wnh = d->wage_next_hours;
  int wnm = d->wage_next_minutes;

  //wage next totals
  int wnm_total = timeInMinutes(wnh,wnm);
  double wn_gross = calcWage(wnm_total,config.wage.WAGE);

  //wage current
  int wch = d->wage_current_hours;
  int wcm = d->wage_current_minutes;

  //wage current totals
  int wcm_total = timeInMinutes(wch,wcm);
  double wc_gross = calcWage(wcm_total,config.wage.WAGE);

  printf("\
Dollar{\n\
  Bank:   $%u\n\
          $%u\n\
  Wallet: $%u\n\
}\n\n",db, dbe, dw);

  printf("\
Coin{\n\
  All{\n\
    Quarters:\t%02u\n\
    Dimes:\t%02u\n\
    Nickels:\t%02u\n\
    Pennies:\t%02u\n\
    Total:\t$%0.2f\n\
  }\n\
  Bank{\n\
    Quarters:\t%02u\n\
    Dimes:\t%02u\n\
    Nickels:\t%02u\n\
    Pennies:\t%02u\n\
    Total:\t$%0.2f\n\
  }\n\
  Rolls{\n\
    $10.00 (x40) Quarters:\t%u\n\
    $ 5.00 (x50) Dimes:\t\t%u\n\
    $ 2.00 (x40) Nickels:\t%u\n\
    $ 0.50 (x50) Pennies:\t%u\n\
    Total:\t\t\t$%0.2f\n\
  }\n\
}\n\n",cq, cd, cn, cp, c_total, cmq, cmd, cmn, cmp, cm_total, crq, crd, crn, crp, cr_total);

  printf("\
Paycheck{\n\
  Next{\n\
    %u:%02u (%0.2f) @ %0.2f/hr = $%0.2f (w/ tax: $%0.2f)\n\
  }\n\
  Current{\n\
    %u:%02u (%0.2f) @ %0.2f/hr = $%0.2f (w/ tax: $%0.2f)\n\
  }\n\
}\n\n",wnh, wnm, timeInHours(wnh,wnm), config.wage.WAGE,wn_gross, wn_gross - tax(wn_gross), wch, wcm, timeInHours(wch,wcm), config.wage.WAGE, wc_gross, wc_gross - tax(wc_gross));

}

static void list_vars(data *d){
  printf("\
Choose a variable to edit:\n\
  Dollar{\n\
    <" YELLOW "1" DEFAULT "> Bank:\t\t%u\n\
    <" YELLOW "2" DEFAULT "> Bank (extra):\t%u\n\
    <" YELLOW "3" DEFAULT "> Wallet:\t\t%u\n\
  }\n\
  Coin{\n\
    <" YELLOW "4" DEFAULT "> Quarters:\t%u\n\
    <" YELLOW "5" DEFAULT "> Dimes:\t\t%u\n\
    <" YELLOW "6" DEFAULT "> Nickels:\t%u\n\
    <" YELLOW "7" DEFAULT "> Pennies:\t%u\n\
  }\n\
  Wage{\n\
    Next{\n\
      <" YELLOW "8" DEFAULT "> Hours:\t%u\n\
      <" YELLOW "9" DEFAULT "> Minutes:\t%u\n\
    }\n\
    Current{\n\
      <" YELLOW "10" DEFAULT "> Hours:\t%u\n\
      <" YELLOW "11" DEFAULT "> Minutes:\t%u\n\
    }\n\
  }\n",d->dollar_bank,d->dollar_bank_extra,d->dollar_wallet, d->coin_q, d->coin_d, d->coin_n, d->coin_p, d->wage_next_hours, d->wage_next_minutes, d->wage_current_hours, d->wage_current_minutes);
}

static void add_to_var(data *d){
  int choice = 0;
  int new_val = 0;
  //list vars w/ values, then choose
  list_vars(d);
  printf(YELLOW "--> " DEFAULT);
  if (scanf(" %d", &choice) == -1)  return;

  switch(choice){
    case 1: // Dollar Bank
      EAV_PROMPT("Dollar->Bank");
      d->dollar_bank += new_val;
      break;
    case 2: // Dollar Bank Extra
      EAV_PROMPT("Dollar->Bank (extra)");
      d->dollar_bank_extra += new_val;
      break;
    case 3: // Dollar Wallet
      EAV_PROMPT("Dollar->Wallet");
      d->dollar_wallet += new_val;
      break;
    case 4: // Coin Quaters
      EAV_PROMPT("Coin->Quarters");
      d->coin_q += new_val;
      break;
    case 5: // Coin Dimes
      EAV_PROMPT("Coin->Dimes");
      d->coin_d += new_val;
      break;
    case 6: // Coin Nickels
      EAV_PROMPT("Coin->Nickels");
      d->coin_n += new_val;
      break;
    case 7: // Coin Pennies
      EAV_PROMPT("Coin->Pennies");
      d->coin_p += new_val;
      break;
    case 8: // Wage Next Hours
      EAV_PROMPT("Wage->Next->Hours");
      d->wage_next_hours += new_val;
      break;
    case 9: // Wage Next Minutes
      EAV_PROMPT("Wage->Next->Minutes");
      d->wage_next_minutes += new_val;
      break;
    case 10: // Wage Currect Hours
      EAV_PROMPT("Wage->Current->Hours");
      d->wage_current_hours += new_val;
      break;
    case 11: // Wage Current Minutes
      EAV_PROMPT("Wage->Current->Minutes");
      d->wage_current_minutes += new_val;
      break;
  }
}

static void edit_var(data *d){
  int choice = 0;
  int new_val = 0;
  //list vars w/ values, then choose
  list_vars(d);
  printf(YELLOW "--> " DEFAULT);
  if (scanf(" %d", &choice) == -1)  return;

  switch(choice){
    case 1: // Dollar Bank
      ENV_PROMPT("Dollar->Bank");
      d->dollar_bank = new_val;
      break;
    case 2: // Dollar Bank Extra
      ENV_PROMPT("Dollar->Bank (extra)");
      d->dollar_bank_extra = new_val;
      break;
    case 3: // Dollar Wallet
      ENV_PROMPT("Dollar->Wallet");
      d->dollar_wallet = new_val;
      break;
    case 4: // Coin Quaters
      ENV_PROMPT("Coin->Quarters");
      d->coin_q = new_val;
      break;
    case 5: // Coin Dimes
      ENV_PROMPT("Coin->Dimes");
      d->coin_d = new_val;
      break;
    case 6: // Coin Nickels
      ENV_PROMPT("Coin->Nickels");
      d->coin_n = new_val;
      break;
    case 7: // Coin Pennies
      ENV_PROMPT("Coin->Pennies");
      d->coin_p = new_val;
      break;
    case 8: // Wage Next Hours
      ENV_PROMPT("Wage->Next->Hours");
      d->wage_next_hours = new_val;
      break;
    case 9: // Wage Next Minutes
      ENV_PROMPT("Wage->Next->Minutes");
      d->wage_next_minutes = new_val;
      break;
    case 10: // Wage Currect Hours
      ENV_PROMPT("Wage->Current->Hours");
      d->wage_current_hours = new_val;
      break;
    case 11: // Wage Current Minutes
      ENV_PROMPT("Wage->Current->Minutes");
      d->wage_current_minutes = new_val;
      break;
  }
}

static void help(){
  printf("\
Commands:\n\
  add\t-- add to data\n\
  edit\t-- edit data\n\
  show\t-- print a report with the existing data\n\
  save\t-- save current data and exit\n\
  exit\t-- exit the program without saving\n\
  help\t-- displays this help message\n");
}

static int compare_strings(char *s1, char *s2){
  return !strcmp(s1,s2);
}

static void exec_command(data *d, char *cmd, char *fname, int *exit_code){
  if(compare_strings(cmd,"help")){
    help();
  }
  if(compare_strings(cmd,"exit")){
    *(exit_code) = 1;
    printf("Exiting...\n");
  }
  if(compare_strings(cmd,"save")){
    file_save(d,fname);
    *(exit_code) = 1;
    printf("Saving and exiting...\n");
  }
  if(compare_strings(cmd,"edit")){
    edit_var(d);
  }
  if(compare_strings(cmd,"add\n") ){
    add_to_var(d);
  }
  if(compare_strings(cmd,"show")){
    render(d);
  }
}

void prompt(data *d, version *v, char *fname){
  char cmd[5];
  int exit_code = 0;
  if(config.interface.DEBUG_MODE){
    printf("DEBUG :: config vars : {\n  WAGE\t\t= %0.2f\n  TAX\t\t= %0.2f\n  FILENAME\t= %s\n}\n", config.wage.WAGE, config.wage.INCOME_TAX, config.data.FILENAME);
  }
  printf("Balance Tool by Braden Best\n");
  print_version(v);
  printf("Type 'help' for a list of commands\n\n");
  while(1){
    printf(BLUE ">>> " DEFAULT);
    if(fgets(cmd,sizeof(cmd),stdin) == NULL){ // Ctrl+D
      printf("\n");
      break;
    }
    printf("%s\n",cmd);
    exec_command(d,cmd,fname,&exit_code);
    if(exit_code)    break;
  }
}/*}}}*/
// get_home/*{{{*/

void get_home(char *str){
  strcpy(str,getenv("HOME"));
  strcat(str,"/.balance_data");
}/*}}}*/
// data/*{{{*/
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
}/*}}}*/
// config/*{{{*/
const global_conf config = {
  {       ""      },
  /*   FILENAME   */
  {       0      },
  /* DEBUG_MODE */
  {  7.5,       13.1   }
  /* WAGE   INCOME_TAX*/
};

// WAGE and INCOME_TAX should become part of struct data, no filename, file should be decided by get_home at runtime. Fuck debug mode/*}}}*/
// main/*{{{*/
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
}/*}}}*/
