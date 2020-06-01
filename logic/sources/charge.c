#include "../includes/charge.h"

charge charge_create(double x, double y, symbol symbol, double force, double weight, short is_fixed) {
    charge ch;
    coordinate c = coordinate_create(x, y);
    ch.position = c;
    ch.symbol = symbol;
    ch.force = force;
    ch.weight = weight;
    ch.is_fixed = is_fixed;
    return ch;
}