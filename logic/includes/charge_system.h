#ifndef CHARGE_SYSTEM
#define CHARGE_SYSTEM

#include <math.h>

#include "charge.h"
#include "vector.h"

#define MAX_CHARGES_NUMBER 100
#define COULOMB_CONST 8.987551787368176E9

typedef struct charge_system_ charge_system;

struct charge_system_ {
    charge* charges[MAX_CHARGES_NUMBER];
    int charges_index;
};

charge_system* charge_system_create();

double coulomb_law(charge *a, charge *b);

vector* superposition_law(charge *charges[], int charges_index, charge *mobile_charge);

void add_charge(charge_system* c_s, charge* ch);

void calculate_next_speed(charge* c, vector* s_l);

void calculate_next_pose(charge *c, vector *s_l);
#endif
