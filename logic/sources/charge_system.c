#include "../includes/charge_system.h"

charge_system charge_system_create(int min_abscissa, int max_abscissa, int min_ordinate, int max_ordinate) {
    charge_system s;
    s.fixed_charges_index = 0;
    s.mobile_charges_index = 0;
    range a = range_create(min_abscissa, max_abscissa);
    range o = range_create(min_ordinate, max_ordinate);
    s.abscissa = a;
    s.ordinate = o;
    return s;
}

double coulomb_law(charge a, charge b) {
    return COULOMB_CONST * (fabs(a.force * b.force)/pow(two_points_distance(a.position, b.position), 2));
}

void add_fixed_charge(charge_system c_s, charge ch) {
    c_s.fixed_charges[c_s.fixed_charges_index++] = ch;
}

void add_mobile_charge(charge_system c_s, charge ch) {
    c_s.mobile_charges[c_s.mobile_charges_index++] = ch;
}