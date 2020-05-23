#include "../includes/charge_system.h"

charge_system charge_system_create(int min_abscissa, int max_abscissa, int min_ordinate, int max_ordinate) {
    charge_system s;
    range a = range_create(min_abscissa, max_abscissa);
    range o = range_create(min_ordinate, max_ordinate);
    s.abscissa = a;
    s.ordinate = o;
    return s;
}

double coulomb_law(double a, double b);