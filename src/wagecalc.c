#include "wagecalc.h"

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
  return gross * (INCOME_TAX / 100);
}
