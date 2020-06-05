#ifndef CHARGE
#define CHARGE

#include "coordinate.h"
#include "enums.h"
#include "../../constant.h"

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

/**
 * charge constructor.
 * 
 * @param x
 * @param y
 * @param symbol
 * @param force
 * @param weight
 * @param is_fixed
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
#endif
