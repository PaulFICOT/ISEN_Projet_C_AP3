#include "../includes/charge_system.h"

charge_system charge_system_create(int min_abscissa, int max_abscissa, int min_ordinate, int max_ordinate) {
    charge_system s;
    range a = range_create(min_abscissa, max_abscissa);
    range o = range_create(min_ordinate, max_ordinate);
    s.abscissa = a;
    s.ordinate = o;
    return s;
}

double coulomb_law(double a, double b, double r) {
    return (1 / (4*PI*EPSILON_0))*((a*b)/(r*r));
}

double two_points_distance(coordinate a, coordinate b) {
    return sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2));
}