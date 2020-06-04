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

/**
 * charge_system constructor.
 *
 * @return a new charge_system instance
 */
charge_system* charge_system_create();

/**
 * Calculate the coulomb law of the charge b on the charge a
 * 
 * @param a a charge
 * @param b a charge
 * 
 * @return the coulomb law
 */
double coulomb_law(charge *a, charge *b);

/**
 * Calculate the superposition law of a group of charges on a charge
 * 
 * @param mobile_charge the charge which is subject to the law
 * @param charges the array containing the charges to apply
 * @param charges_index the index of the charges array
 * 
 * @return the vector representing the superposition law
 */
vector* superposition_law(charge* mobile_charge, charge *charges[], int charges_index);

/**
 * Append a charge to a charge_system charges array
 * 
 * @param c_s the charge_system
 * @param ch a charge
 */
void add_charge(charge_system* c_s, charge* ch);

/**
 * Calculate the speed of a charge
 * 
 * @param c the charge
 * @param charges the array containing all the charges which will apply a force
 * @param charges_index the index of the charges array
 */
void calculate_next_speed(charge* c, charge* charges[], int charges_index);

/**
 * Calculate the position of a charge
 * 
 * @param c the charge
 * @param charges the array containing all the charges which will apply a force
 * @param charges_index the index of the charges array
 */
void calculate_next_pose(charge* c, charge* charges[], int charges_index);
#endif
