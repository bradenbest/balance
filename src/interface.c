#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "data.h"
#include "wagecalc.h"
#include "version.h"
#include "config.h"

#include "interface.h"

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
  Bank:   $%i\n\
          $%i\n\
  Wallet: $%i\n\
}\n\n",db, dbe, dw);

  printf("\
Coin{\n\
  All{\n\
    Quarters:\t%02i\n\
    Dimes:\t%02i\n\
    Nickels:\t%02i\n\
    Pennies:\t%02i\n\
    Total:\t$%0.2f\n\
  }\n\
  Bank{\n\
    Quarters:\t%02i\n\
    Dimes:\t%02i\n\
    Nickels:\t%02i\n\
    Pennies:\t%02i\n\
    Total:\t$%0.2f\n\
  }\n\
  Rolls{\n\
    $10.00 (x40) Quarters:\t%i\n\
    $ 5.00 (x50) Dimes:\t\t%i\n\
    $ 2.00 (x40) Nickels:\t%i\n\
    $ 0.50 (x50) Pennies:\t%i\n\
    Total:\t\t\t$%0.2f\n\
  }\n\
}\n\n",cq, cd, cn, cp, c_total, cmq, cmd, cmn, cmp, cm_total, crq, crd, crn, crp, cr_total);

  printf("\
Paycheck{\n\
  Next{\n\
    %i:%02i (%0.2f) @ %0.2f/hr = $%0.2f (w/ tax: $%0.2f)\n\
  }\n\
  Current{\n\
    %i:%02i (%0.2f) @ %0.2f/hr = $%0.2f (w/ tax: $%0.2f)\n\
  }\n\
}\n\n",wnh, wnm, timeInHours(wnh,wnm), config.wage.WAGE,wn_gross, wn_gross - tax(wn_gross), wch, wcm, timeInHours(wch,wcm), config.wage.WAGE, wc_gross, wc_gross - tax(wc_gross));

}

static void list_vars(data *d){
  printf("\
Choose a variable to edit:\n\
  Dollar{\n\
    <" YELLOW "1" DEFAULT "> Bank:\t\t%i\n\
    <" YELLOW "2" DEFAULT "> Bank (extra):\t%i\n\
    <" YELLOW "3" DEFAULT "> Wallet:\t\t%i\n\
  }\n\
  Coin{\n\
    <" YELLOW "4" DEFAULT "> Quarters:\t%i\n\
    <" YELLOW "5" DEFAULT "> Dimes:\t\t%i\n\
    <" YELLOW "6" DEFAULT "> Nickels:\t%i\n\
    <" YELLOW "7" DEFAULT "> Pennies:\t%i\n\
  }\n\
  Wage{\n\
    Next{\n\
      <" YELLOW "8" DEFAULT "> Hours:\t%i\n\
      <" YELLOW "9" DEFAULT "> Minutes:\t%i\n\
    }\n\
    Current{\n\
      <" YELLOW "10" DEFAULT "> Hours:\t%i\n\
      <" YELLOW "11" DEFAULT "> Minutes:\t%i\n\
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
    printf("DEBUG MODE {\n  WAGE\t\t= %0.2f\n  TAX\t\t= %0.2f\n  FILENAME\t= %s\n  MAXFS\t\t= %i\n}\n", config.wage.WAGE, config.wage.INCOME_TAX, config.data.FILENAME, config.data.MAXFS);
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
}
