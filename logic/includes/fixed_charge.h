#include "coordinate.h"
#include "enums.h"

typedef struct fixed_charge_ fixed_charge;

struct fixed_charge_ {
    coordinate position;
    charge charge;
    double force;
};

fixed_charge fixed_charge_create(double x, double y, charge charge, double force);