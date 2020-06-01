#ifndef CHARGE
#define CHARGE

#include "coordinate.h"
#include "enums.h"

typedef struct charge_ charge;

struct charge_ {
    coordinate position;
    symbol symbol;
    double force;
    double weight;
    short is_fixed;
};

charge charge_create(double x, double y, symbol symbol, double force, double weight, short is_fixed);

#endif