#ifndef CHARGE_SYSTEM
#define CHARGE_SYSTEM

#include <math.h>

#include "charge.h"
#include "vector.h"
#include "../../constants.h"
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
 * Fetch the current element of the linked_list's charges
 *
 * @param c_s the charge system
 *
 * @return the current charge
 */
charge* current_charge(charge_system* c_s);

/**
 * Append a charge to the charge system
 *
 * @param c_s the charge_system
 * @param ch a charge
 */
void add_charge(charge_system* c_s, charge* ch);

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
 * @param c_s The charge system with all coordinates charge
 * @param coord The coordinate to check
 */
short charge_is_placeable(charge_system* c_s, coordinate* coord);

/**
 * Get the charge in the charge system at the coordinate given
 *
 * @param coord The coordinate to check
 * @param main_charge_system The charge system with all charges
 */
charge* get_charge(charge_system* c_s, coordinate* coord);

/**
 * Reset the charges in the charge system
 *
 * @param c_s the charge_system
 */
void reset_charge_system(charge_system* c_s);

/**
 * Print the charges in the charges linked_list
 */
void print_charge(charge_system* c_s);

/**
 * Calculate the electrostatic potential of a charge
 *
 * @param q the charge
 * @param m the coordinate of the other point you would like to get the electrostatic potential
 */
float electrostatic_potential(charge* q, coordinate* m);

#endif
