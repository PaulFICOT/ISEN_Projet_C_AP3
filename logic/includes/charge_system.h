#ifndef CHARGE_SYSTEM
#define CHARGE_SYSTEM

#include <math.h>

#include "charge.h"
#include "vector.h"
#include "../../constant.h"
#include "linked_list.h"

typedef struct charge_system_ charge_system;

struct charge_system_ {
    linked_list* charges;
};

/**
 * charge_system constructor.
 *
 * @return a new charge_system instance
 */
charge_system* charge_system_create();

/**
 * Calculate the superposition law of a group of charges on a charge
 * 
 * @param mobile_charge the charge which is subject to the law
 * @param charges the array containing the charges to apply
 * @param charges_index the index of the charges array
 * 
 * @return the vector representing the superposition law
 */
vector* superposition_law(charge_system* c_s, charge* mobile_charge);

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
void calculate_next_speed(charge_system* c_s, charge* c);

/**
 * Calculate the position of a charge
 * 
 * @param c the charge
 * @param charges the array containing all the charges which will apply a force
 * @param charges_index the index of the charges array
 */
void calculate_next_pose(charge_system* c_s, charge* c);

/**
 * Check if the charge is placeable at the coordinate
 * 
 * @param coord The coordinate to check
 * @param main_charge_system The charge system with all coordinates charge
 */
short charge_is_placeable(coordinate* coord, charge_system* main_charge_system);
#endif
