#ifndef CHARGE_SYSTEM
#define CHARGE_SYSTEM

#include <math.h>

#include "charge.h"
#include "vector.h"
#include "../../constants.h"
#include "linked_list.h"
#include "distance_converter.h"

typedef struct charge_system_ charge_system;

struct charge_system_ {
    linked_list* charges;
};

/**
 * Charge_system constructor.
 *
 * @return a new charge_system instance
 */
charge_system* charge_system_create();

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
 * @param c_s the charge system
 * @param mobile_charge the charge which is subject to the law
 *
 * @return the vector representing the superposition law
 */
vector* superposition_law(charge_system* c_s, charge* mobile_charge);

/**
 * Calculate the position of a charge
 *
 * @param c_s the charge system
 * @param c the charge
 * @param enable_collision a boolean to toggle if the charges can collide
 */
void calculate_next_pose(charge_system* c_s, charge* c, short enable_collisions);

/**
 * Checks if a charge won't collide with another charge while its translation
 *
 * @param c_s the charge system
 * @param c the charge
 *
 * @return 0 if there is a collision
 */
short charge_is_moveable(charge_system* c_s, coordinate* c);

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
 * @param c_s The charge system with all charges
 * @param coord The coordinate to check
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
 *
 * @param c_s the charge system
 */
void print_charge(charge_system* c_s);

/**
 * Calculate the electrostatic potential of a charge
 *
 * @param q the charge
 * @param m the coordinate of the other point you would like to get the electrostatic potential
 */
double electrostatic_potential(charge_system* c_s, coordinate* m);

#endif
