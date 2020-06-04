#ifndef CHARGE
#define CHARGE

#include "coordinate.h"
#include "enums.h"
#define MAX_ENTRIES 50

typedef struct charge_ charge;

struct charge_ {
    coordinate* position;
    enum symbol symbol;
    double force;
    double weight;
    short is_fixed;
    coordinate* positions[MAX_ENTRIES];
    int positions_index;
    double speeds[MAX_ENTRIES];
    int speeds_index;
};

charge* charge_create(double x, double y, enum symbol symbol, double force, double weight, short is_fixed);

short charge_is_itself(charge* ca, charge* cb);
#endif
