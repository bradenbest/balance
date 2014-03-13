#define WAGECALC_H
#include "config.h"

#ifndef WAGE
#  define WAGE 7.5
#endif

#ifndef INCOME_TAX
#  define INCOME_TAX 1.0
#endif

double calcWage(int minutes, double wage);
int timeInMinutes(int hours, int minutes);
double timeInHours(int hours, int minutes);
double tax(double gross);
