#include "../includes/charge.h"

charge charge_create(double x, double y, symbol symbol, double force) {
    charge f_c;
    coordinate c = coordinate_create(x, y);
    f_c.position = c;
    f_c.symbol = symbol;
    f_c.force = force;
    return f_c;
}