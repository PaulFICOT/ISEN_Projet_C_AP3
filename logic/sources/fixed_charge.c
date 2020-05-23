#include "../includes/fixed_charge.h"

fixed_charge fixed_charge_create(double x, double y, charge charge, double force) {
    fixed_charge f_c;
    coordinate c = coordinate_create(x, y);
    f_c.position = c;
    f_c.charge = charge;
    f_c.force = force;
    return f_c;
}