#ifndef CHARGE
#define CHARGE

#include "coordinate.h"
#include "../../enums.h"
#include "../../constants.h"

typedef struct charge_ charge;

struct charge_ {
    coordinate* position;
    coordinate* last_position;
    coordinate* speed;
    coordinate* last_speed;
    enum symbol symbol;
    double force;
    double weight;
    short is_fixed;
    double time;
};

/**
 * charge constructor.
 *
 * @param x the x coordinates
 * @param y the y coordinates
 * @param symbol if the charge is positive or negative
 * @param force the force of the charge
 * @param weight the weight of the charge
 * @param is_fixed if the charge is fixed or mobile
 *
 * @return a new charge instance
 */
charge* charge_create(double x, double y, enum symbol symbol, double force, double weight, short is_fixed);

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
 * Check if two charges are the same
 *
 * @param a a charge
 * @param b a charge
 *
 * @return true if the two charges are the same, false otherwise
 */
short charge_is_itself(charge* a, charge* b);

/**
 * Generates a charge generated randomly
 *
 * @param is_fixed 1 -> charge is fixed 0 -> charge is mobile
 *
 * @return a charge
 */
charge* random_charge(double x, double y, double is_fixed);
#endif
