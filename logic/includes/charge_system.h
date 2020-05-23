#include <math.h>

#include "fixed_charge.h"
#include "range.h"

#define MAX_CHARGES_NUMBER 50
#define PI 3.14159265358979323846
#define EPSILON_0 8.85418782E-12
#define COULOMB_CONST 8.987551787368176E9

typedef struct charge_system_ charge_system;

struct charge_system_ {
    fixed_charge fixed_charges[MAX_CHARGES_NUMBER];
    range abscissa;
    range ordinate;
};

charge_system charge_system_create(int min_abscissa, int max_abscissa, int min_ordinate, int max_ordinate);

double coulomb_law(double a, double b, double r);

double two_points_distance(coordinate a, coordinate b);