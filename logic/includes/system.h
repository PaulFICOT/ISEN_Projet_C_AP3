#include "fixed_charge.h"
#include "range.h"
#define MAX_CHARGES_NUMBER 50

#define EPSILON_0 8.654E-12

typedef struct system_ system;

struct system_ {
    fixed_charge fixed_charges[MAX_CHARGES_NUMBER];
    range abscissa;
    range ordinate;
};

system system_create(int min_abscissa, int max_abscissa, int min_ordinate, int max_ordinate);

double coulon_law(double a, double b);